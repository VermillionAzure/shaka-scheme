#include <gmock/gmock.h>
#include <shaka_scheme/system/core/vectors.hpp>
#include <shaka_scheme/system/base/DataPair.hpp>

/**
 * @brief Test: Testing (list->vector l)
 */
TEST(VectorsUnitTest, list_to_vector_3_elements) {
  using namespace shaka;
  const auto& c = shaka::create_node;

  // Given: a list of three numbers
  NodePtr node = core::list(
      c(Number(1)),
      c(Number(2)),
      c(Number(3))
  );

  // When: you apply (list->vector)
  shaka::Vector v(std::move(core::list_to_vector(node)->get<shaka::Vector>()));

  // Then: you should be able to get a shaka::Vector out of it
  ASSERT_EQ(v.length(), 3);

  // Then: the elements should be #(1 2 3)
  ASSERT_EQ(v[0]->get<Number>(), Number(1));
  ASSERT_EQ(v[1]->get<Number>(), Number(2));
  ASSERT_EQ(v[2]->get<Number>(), Number(3));
}

/**
 * @brief Test: Testing (list->vector l)
 */
TEST(VectorsUnitTest, vector_to_list_2_elements) {
  using namespace shaka;
  const auto& c = shaka::create_node;

  // Given: a vector of 3 items
  NodePtr node = c(shaka::Vector({
                                     c(Number(1)),
                                     c(Number(2)),
                                     c(Number(3))
                                 }));

  // When: you apply (vector->list) and get the result
  NodePtr result = core::vector_to_list(node);

  // Then: the result should be a proper list
  ASSERT_TRUE(core::is_proper_list(result));

  // Then: the elements should be (1 2 3)
  ASSERT_EQ(result->get<DataPair>()
                .car()
                ->get<Number>(),
            Number(1));
  ASSERT_EQ(result->get<DataPair>()
                .cdr()
                ->get<DataPair>()
                .car()
                ->get<Number>(),
            Number(2));
  ASSERT_EQ(result->get<DataPair>()
                .cdr()
                ->get<DataPair>()
                .cdr()
                ->get<DataPair>()
                .car()
                ->get<Number>(),
            Number(3));
  ASSERT_EQ(result->get<DataPair>()
                .cdr()
                ->get<DataPair>()
                .cdr()
                ->get<DataPair>()
                .cdr()->get_type(),
            shaka::Data::Type::NULL_LIST);
}