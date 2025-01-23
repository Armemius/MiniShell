#pragma once

#include <string>
#include <vector>

namespace minsh::parser {

/**
 * \brief Tokenizes the input string into a vector of strings.
 *
 * This function takes an input string and splits it into tokens based on
 * whitespace or other delimiters.
 *
 * \param input The input string to be tokenized.
 * \return A vector of strings, each representing a token from the input.
 */
std::vector<std::string> tokenize(const std::string &input);

}
