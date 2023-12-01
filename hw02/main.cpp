#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>

#include <chrono>

#endif
struct Node {
	char value;
	size_t index;
	Node *left, *right;
	Node(char value, int index) : value(value), index(index), left(nullptr), right(nullptr) {}
};

struct TextEditorBackend{
	Node *root = nullptr;
	size_t size_ = 0, lines_ = 1;

	TextEditorBackend(const std::string& text){
		for (const auto& c : text){
			if (c == '\n') lines_++;
			root = insert(root, c, size_++);
		}
	}
    ~TextEditorBackend(){
        destroy(root);
    }

    void destroy(Node* node){
        if (node){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void insert(size_t i, char c){
		if (i > size_) throw std::out_of_range("insert out of range");
		
		if (c == '\n') lines_++;
		size_++;
		root = insert(root, c, i);
	}

	Node* insert(Node* node, char c, size_t i){
		if (!node) return new Node(c, 0);

		size_t leftIndex = (node->left ? node->left->index : 0);
		if (i <= leftIndex){
			node->left = insert(node->left, c, i);
			return rotateRight(node);
		}
		node->right = insert(node->right, c, i - leftIndex - 1);
		return rotateLeft(node);
	}

	Node* rotateRight(Node* node){
		Node* x = node->left;
		node->left = x->right;
		x->right = node;
		x->index = node->index;
		node->index = 1 + (node->left ? node->left->index : 0) + (node->right ? node->right->index : 0);
		return x;
	}

	Node* rotateLeft(Node* node){
		Node* x = node->right;
		node->right = x->left;
		x->left = node;
		x->index = node->index;
		node->index = 1 + (node->left ? node->left->index : 0) + (node->right ? node->right->index : 0);
		return x;
	}

	void erase(size_t i){
		if (i >= size()) throw std::out_of_range("erase out of range");
		if (at(i) == '\n') lines_--;
		root = erase(root, i);
		size_--;
	}

	Node* erase(Node* node, size_t i){
		if (!node) throw std::out_of_range("*erase out of range");

		size_t leftIndex = (node->left) ? node->left->index : 0;
		if (i < leftIndex)
			node->left = erase(node->left, i);
		else if (i > leftIndex)
			node->right = erase(node->right, i - leftIndex - 1);
		else{
			if (!node->left){
				Node *temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right){
				Node *temp = node->left;
				delete node;
				return temp;
			}
			
			Node* temp = node->right;
			while(temp && temp->left)
				temp = temp->left;
	
			node->value = temp->value;
			node->right = erase(node->right, 0);
		}
		node->index--;
		return node;
	}

	void edit(size_t i, char c){
		if (i >= size_) throw std::out_of_range("edit out of range");
		erase(i);
		insert(i, c);
	}

	size_t magic(Node* node, size_t num, bool flag, size_t& index, size_t& lines) const{
		if (!node) return 0;
		
		auto res = magic(node->left, num, flag, index, lines);
		if (res) return res;

		if (flag){ //char_to_line
			if (index == num) return lines;
			if (node->value == '\n') lines++;
		}
		else{ //line_start
			if (node->value == '\n'){
				lines++;
				if (lines == num) return index + 1;
			}
		}
		return magic(node->right, num, flag, ++index, lines);
	}

	size_t line_start(size_t r) const {
		if (r >= lines()) throw std::out_of_range("line_start out of range");
		size_t index = 0, lines = 0;
		return magic(root, r, false, index, lines);
	}

	size_t char_to_line(size_t i) const{
		if (i >= size()) throw std::out_of_range("char_to_line out of range");
		size_t lines = 0, index = 0;
		return magic(root, i, true, index, lines);
	}

	size_t line_length(size_t r) const {
		if (r >= lines()) throw std::out_of_range("line_length out of range");

		size_t start = line_start(r);
		if (r + 1 < lines()) 
            return line_start(r + 1) - start;
		return size() - start;
	}

	char at(size_t i) const{
		if (i >= size_) throw std::out_of_range("at out of range");
		
		Node *node = root;
		while (node != nullptr){
			size_t leftIndex = (node->left) ? node->left->index : 0;
			if (i < leftIndex)
				node = node->left;
			else if (i > leftIndex){
				node = node->right;
				i -= leftIndex + 1;
			}
			else
				return node->value;
		}
		return '\0';
	}

	size_t size() const{
		return size_;
	}

	size_t lines() const{
		return lines_;
	}
};

#ifndef __PROGTEST__

////////////////// Dark magic, ignore ////////////////////////

template <typename T>
auto quote(const T &t) { return t; }

std::string quote(const std::string &s)
{
	std::string ret = "\"";
	for (char c : s)
		if (c != '\n')
			ret += c;
		else
			ret += "\\n";
	return ret + "\"";
}

#define STR_(a) #a
#define STR(a) STR_(a)

#define CHECK_(a, b, a_str, b_str)                                   \
	do                                                               \
	{                                                                \
		auto _a = (a);                                               \
		decltype(a) _b = (b);                                        \
		if (_a != _b)                                                \
		{                                                            \
			std::cout << "Line " << __LINE__ << ": Assertion "       \
					  << a_str << " == " << b_str << " failed!"      \
					  << " (lhs: " << quote(_a) << ")" << std::endl; \
			fail++;                                                  \
		}                                                            \
		else                                                         \
			ok++;                                                    \
	} while (0)

#define CHECK(a, b) CHECK_(a, b, #a, #b)

#define CHECK_ALL(expr, ...)                                                    \
	do                                                                          \
	{                                                                           \
		std::array _arr = {__VA_ARGS__};                                        \
		for (size_t _i = 0; _i < _arr.size(); _i++)                             \
			CHECK_((expr)(_i), _arr[_i], STR(expr) "(" << _i << ")", _arr[_i]); \
	} while (0)

#define CHECK_EX(expr, ex)                                                                                                             \
	do                                                                                                                                 \
	{                                                                                                                                  \
		try                                                                                                                            \
		{                                                                                                                              \
			(expr);                                                                                                                    \
			fail++;                                                                                                                    \
			std::cout << "Line " << __LINE__ << ": Expected " STR(expr) " to throw " #ex " but no exception was raised." << std::endl; \
		}                                                                                                                              \
		catch (const ex &)                                                                                                             \
		{                                                                                                                              \
			ok++;                                                                                                                      \
		}                                                                                                                              \
		catch (...)                                                                                                                    \
		{                                                                                                                              \
			fail++;                                                                                                                    \
			std::cout << "Line " << __LINE__ << ": Expected " STR(expr) " to throw " #ex " but got different exception." << std::endl; \
		}                                                                                                                              \
	} while (0)

////////////////// End of dark magic ////////////////////////

std::string text(const TextEditorBackend& t) {
	std::string ret;
	for (size_t i = 0; i < t.size(); i++) ret.push_back(t.at(i));
	return ret;
}

void test1(int &ok, int &fail)
{
	TextEditorBackend s("123\n456\n789");
	CHECK(s.size(), 11);
	CHECK(text(s), "123\n456\n789");
	CHECK(s.lines(), 3);
	CHECK_ALL(s.char_to_line, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2);
	CHECK_ALL(s.line_start, 0, 4, 8);
	CHECK_ALL(s.line_length, 4, 4, 3);
}

void test2(int &ok, int &fail)
{
	TextEditorBackend t("123\n456\n789\n");
	CHECK(t.size(), 12);
	CHECK(text(t), "123\n456\n789\n");
	CHECK(t.lines(), 4);
	CHECK_ALL(t.char_to_line, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2);
	CHECK_ALL(t.line_start, 0, 4, 8, 12);
	CHECK_ALL(t.line_length, 4, 4, 4, 0);
}

void test3(int &ok, int &fail){
	TextEditorBackend t("asdfasdfasdf");

	CHECK(t.size(), 12);
	CHECK(text(t), "asdfasdfasdf");
	CHECK(t.lines(), 1);
	CHECK_ALL(t.char_to_line, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	CHECK(t.line_start(0), 0);
	CHECK(t.line_length(0), 12);

	t.insert(0, '\n');
	CHECK(t.size(), 13);
	CHECK(text(t), "\nasdfasdfasdf");
	CHECK(t.lines(), 2);
	CHECK_ALL(t.line_start, 0, 1);

	t.insert(4, '\n');
	CHECK(t.size(), 14);
	CHECK(text(t), "\nasd\nfasdfasdf");
	CHECK(t.lines(), 3);
	CHECK_ALL(t.line_start, 0, 1, 5);

	t.insert(t.size(), '\n');
	CHECK(t.size(), 15);
	CHECK(text(t), "\nasd\nfasdfasdf\n");
	CHECK(t.lines(), 4);
	CHECK_ALL(t.line_start, 0, 1, 5, 15);

	t.edit(t.size() - 1, 'H');
	CHECK(t.size(), 15);
	CHECK(text(t), "\nasd\nfasdfasdfH");
	CHECK(t.lines(), 3);
	CHECK_ALL(t.line_start, 0, 1, 5);

	t.erase(8);
	CHECK(t.size(), 14);
	CHECK(text(t), "\nasd\nfasfasdfH");
	CHECK(t.lines(), 3);
	CHECK_ALL(t.line_start, 0, 1, 5);

	t.erase(4);
	CHECK(t.size(), 13);
	CHECK(text(t), "\nasdfasfasdfH");
	CHECK(t.lines(), 2);
	CHECK_ALL(t.line_start, 0, 1);
}

void test_ex(int &ok, int &fail)
{
	TextEditorBackend t("123\n456\n789\n");
	CHECK_EX(t.at(12), std::out_of_range);

	CHECK_EX(t.insert(13, 'a'), std::out_of_range);
	CHECK_EX(t.edit(12, 'x'), std::out_of_range);
	CHECK_EX(t.erase(12), std::out_of_range);

	CHECK_EX(t.line_start(4), std::out_of_range);
	CHECK_EX(t.line_start(40), std::out_of_range);
	CHECK_EX(t.line_length(4), std::out_of_range);
	CHECK_EX(t.line_length(6), std::out_of_range);
	CHECK_EX(t.char_to_line(12), std::out_of_range);
	CHECK_EX(t.char_to_line(25), std::out_of_range);
}

int main(){
	// TextEditorBackend t("ahojky");
	// t.insert(0, 'X');
	// std::cout << text(t) << std::endl;


	int ok = 0, fail = 0;
	if (!fail)
		test1(ok, fail);
	if (!fail)
		test2(ok, fail);
	if (!fail)
		test3(ok, fail);
	if (!fail)
		test_ex(ok, fail);

	if (!fail)
		std::cout << "Passed all " << ok << " tests!" << std::endl;
	else
		std::cout << "Failed " << fail << " of " << (ok + fail) << " tests." << std::endl;
}

#endif