#include <gtest/gtest.h>

#include <parser/tokenize.hpp>

TEST(ParserTest, TestEmpty) {
  auto tokens = minsh::parser::tokenize("");
  EXPECT_EQ(tokens.size(), 0);

  tokens = minsh::parser::tokenize("       ");
  EXPECT_EQ(tokens.size(), 0);
}

TEST(ParserTest, TestSingle) {
  auto tokens = minsh::parser::tokenize("single");
  EXPECT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0], "single");

  tokens = minsh::parser::tokenize("         single");
  EXPECT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0], "single");

  tokens = minsh::parser::tokenize("single        ");
  EXPECT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0], "single");

  tokens = minsh::parser::tokenize("   single    ");
  EXPECT_EQ(tokens.size(), 1);
  EXPECT_EQ(tokens[0], "single");
}

TEST(ParserTest, TestMultiple) {
  auto tokens = minsh::parser::tokenize("one two three");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "one");
  EXPECT_EQ(tokens[1], "two");
  EXPECT_EQ(tokens[2], "three");

  tokens = minsh::parser::tokenize("one    two  three");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "one");
  EXPECT_EQ(tokens[1], "two");
  EXPECT_EQ(tokens[2], "three");

  tokens = minsh::parser::tokenize("       one    two  three    ");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "one");
  EXPECT_EQ(tokens[1], "two");
  EXPECT_EQ(tokens[2], "three");
}

TEST(ParserTest, TestQuoted) {
  auto tokens = minsh::parser::tokenize(R"(i am "a string")");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], "a string");

  tokens = minsh::parser::tokenize("i am 'a string'");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], "a string");

  tokens = minsh::parser::tokenize(R"(i am "'a string'")");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], "'a string'");

  tokens = minsh::parser::tokenize(R"(i am '"a string"')");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], R"("a string")");
}

TEST(ParserTest, TestShielding) {
  auto tokens = minsh::parser::tokenize(R"(i am "a string with \"")");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], R"(a string with ")");

  tokens = minsh::parser::tokenize(R"(i am 'a string with \'')");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], "a string with '");

  tokens = minsh::parser::tokenize(R"(i am 'a string with \\')");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens[0], "i");
  EXPECT_EQ(tokens[1], "am");
  EXPECT_EQ(tokens[2], "a string with \\");
}
