#include "xunique_ptr.h"

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

// 所有权约束属于编译期契约；违反时测试目标应直接编译失败。
static_assert(!std::is_copy_constructible_v<XuniquePtr<int>>);
static_assert(!std::is_copy_assignable_v<XuniquePtr<int>>);
static_assert(std::is_nothrow_move_constructible_v<XuniquePtr<int>>);
static_assert(std::is_nothrow_move_assignable_v<XuniquePtr<int>>);
static_assert(!std::is_convertible_v<int*, XuniquePtr<int>>);

namespace
{
// 记录每个对象的析构顺序，检查旧资源释放、所有权转移和最终销毁。
struct Tracked
{
    int value;
    std::vector<int>& destroyed;

    Tracked(int value, std::vector<int>& destroyed)
        : value(value), destroyed(destroyed) {}

    ~Tracked() { destroyed.push_back(value); }
};

class XuniquePtrTest : public ::testing::Test
{
  protected:
    std::vector<int> destroyed;

    Tracked* make(int value) { return new Tracked(value, destroyed); }
};

TEST_F(XuniquePtrTest, DefaultConstructorIsEmpty)
{
    XuniquePtr<Tracked> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_TRUE(destroyed.empty());
}

TEST_F(XuniquePtrTest, NullPointerConstructorIsEmpty)
{
    XuniquePtr<Tracked> ptr(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(XuniquePtrTest, OwnsRawPointerAndDestroysItOnce)
{
    auto* raw = make(1);
    {
        XuniquePtr<Tracked> ptr(raw);
        EXPECT_EQ(ptr.get(), raw);
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, DereferenceReadsAndModifiesObject)
{
    XuniquePtr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
    *ptr = 7;
    EXPECT_EQ(*ptr, 7);
    EXPECT_EQ(&*ptr, ptr.get());
}

TEST_F(XuniquePtrTest, ArrowAccessesObject)
{
    XuniquePtr<Tracked> ptr(make(1));
    EXPECT_EQ(ptr.operator->(), ptr.get());
    EXPECT_EQ(ptr->value, 1);
    ptr->value = 2;
    EXPECT_EQ(ptr->value, 2);
}

TEST_F(XuniquePtrTest, ConstOwnerCanAccessPointee)
{
    const XuniquePtr<int> ptr(new int(42));
    EXPECT_EQ(*ptr, 42);
    EXPECT_EQ(ptr.operator->(), ptr.get());
    *ptr = 7;
    EXPECT_EQ(*ptr, 7);
}

TEST_F(XuniquePtrTest, MoveConstructorTransfersOwnership)
{
    {
        XuniquePtr<Tracked> source(make(1));
        auto* raw = source.get();
        {
            XuniquePtr<Tracked> destination(std::move(source));
            EXPECT_EQ(source.get(), nullptr);
            EXPECT_EQ(destination.get(), raw);
            EXPECT_TRUE(destroyed.empty());
        }
        EXPECT_EQ(destroyed, std::vector<int>{1});
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, MoveConstructorAcceptsEmptySource)
{
    XuniquePtr<Tracked> source;
    XuniquePtr<Tracked> destination(std::move(source));
    EXPECT_EQ(source.get(), nullptr);
    EXPECT_EQ(destination.get(), nullptr);
}

TEST_F(XuniquePtrTest, MoveAssignmentReleasesOldResourceAndTransfersOwnership)
{
    {
        XuniquePtr<Tracked> source(make(1));
        XuniquePtr<Tracked> destination(make(2));
        auto* raw = source.get();
        auto& result = (destination = std::move(source));
        EXPECT_EQ(&result, &destination);
        EXPECT_EQ(source.get(), nullptr);
        EXPECT_EQ(destination.get(), raw);
        EXPECT_EQ(destroyed, std::vector<int>{2});
    }
    EXPECT_EQ(destroyed, (std::vector<int>{2, 1}));
}

TEST_F(XuniquePtrTest, MoveAssignmentIntoEmptyDestination)
{
    {
        XuniquePtr<Tracked> source(make(1));
        XuniquePtr<Tracked> destination;
        auto* raw = source.get();
        destination = std::move(source);
        EXPECT_EQ(source.get(), nullptr);
        EXPECT_EQ(destination.get(), raw);
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, MoveAssignmentFromEmptySourceReleasesDestination)
{
    {
        XuniquePtr<Tracked> source;
        XuniquePtr<Tracked> destination(make(1));
        destination = std::move(source);
        EXPECT_EQ(source.get(), nullptr);
        EXPECT_EQ(destination.get(), nullptr);
        EXPECT_EQ(destroyed, std::vector<int>{1});
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, MoveAssignmentBetweenEmptyPointers)
{
    XuniquePtr<Tracked> source;
    XuniquePtr<Tracked> destination;
    destination = std::move(source);
    EXPECT_EQ(source.get(), nullptr);
    EXPECT_EQ(destination.get(), nullptr);
    EXPECT_TRUE(destroyed.empty());
}

TEST_F(XuniquePtrTest, SelfMoveAssignmentPreservesResource)
{
    {
        XuniquePtr<Tracked> ptr(make(1));
        auto* raw = ptr.get();
        auto& alias = ptr;
        auto& result = (ptr = std::move(alias));
        EXPECT_EQ(&result, &ptr);
        EXPECT_EQ(ptr.get(), raw);
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, ReleaseTransfersOwnershipWithoutDeleting)
{
    std::unique_ptr<Tracked> released;
    {
        XuniquePtr<Tracked> ptr(make(1));
        auto* raw = ptr.get();
        released.reset(ptr.release());
        EXPECT_EQ(released.get(), raw);
        EXPECT_EQ(ptr.get(), nullptr);
        EXPECT_EQ(ptr.release(), nullptr);
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_TRUE(destroyed.empty());
    released.reset();
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, ReleaseEmptyPointerReturnsNull)
{
    XuniquePtr<Tracked> ptr;
    EXPECT_EQ(ptr.release(), nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(XuniquePtrTest, ResetReplacesAndDeletesOldResource)
{
    {
        XuniquePtr<Tracked> ptr(make(1));
        auto* replacement = make(2);
        ptr.reset(replacement);
        EXPECT_EQ(ptr.get(), replacement);
        EXPECT_EQ(destroyed, std::vector<int>{1});
    }
    EXPECT_EQ(destroyed, (std::vector<int>{1, 2}));
}

TEST_F(XuniquePtrTest, ResetWithoutArgumentDeletesResource)
{
    {
        XuniquePtr<Tracked> ptr(make(1));
        ptr.reset();
        EXPECT_EQ(ptr.get(), nullptr);
        EXPECT_EQ(destroyed, std::vector<int>{1});
        ptr.reset();
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, ResetWithNullDeletesResource)
{
    XuniquePtr<Tracked> ptr(make(1));
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, ResetEmptyPointerAcquiresResource)
{
    {
        XuniquePtr<Tracked> ptr;
        auto* raw = make(1);
        ptr.reset(raw);
        EXPECT_EQ(ptr.get(), raw);
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_EQ(destroyed, std::vector<int>{1});
}

TEST_F(XuniquePtrTest, MovedFromPointerCanBeReused)
{
    {
        XuniquePtr<Tracked> source(make(1));
        XuniquePtr<Tracked> destination(std::move(source));
        source.reset(make(2));
        EXPECT_EQ(source->value, 2);
        EXPECT_EQ(destination->value, 1);
        EXPECT_NE(source.get(), destination.get());
        EXPECT_TRUE(destroyed.empty());
    }
    EXPECT_EQ(destroyed, (std::vector<int>{1, 2}));
}
} // namespace
