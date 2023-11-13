#pragma once

#include <string>
#include <memory>
#include <vector>
#include <string_view>
#include <iostream>

#include "Types.h"

class Trie
{
public:
    Trie();
    Trie(const Trie& trie) = default;
    ~Trie() = default;

    /* functions */
    void insert(const std::string_view& word) noexcept;
    bool search(const std::string_view& word) const noexcept;
    void print() const noexcept;
    std::vector<std::string> allStrings() const noexcept;

private:
    struct Node 
    {
        Node() : m_isLeaf(false), m_data(static_cast<char>(Characters::UNDEFINED_CHARACTER)),
             m_children() { }
        Node(const char data) : m_data(data), m_isLeaf(false), m_children() { }

        /* functions */
        void print(std::string& buffer, const std::string prefix, const std::string childrenPrefix) const noexcept
        {
            buffer += prefix + m_data + '\n';

            for(const auto& it : m_children)
            {
                if(!it.m_isLeaf)
                {
                    it.print(buffer, childrenPrefix + "├── ", childrenPrefix + "│   ");
                }
                else
                {
                    it.print(buffer, childrenPrefix + "└── ", childrenPrefix + "    ");
                }
            }
        }

        void allStrings(std::string word, std::vector<std::string>& words) const noexcept
        {
            if(m_isLeaf)
            {
                words.push_back(word + m_data);
            }

            for(const auto& it : m_children)
            {
                it.allStrings(word + m_data, words);
            }
        }

        /* members */
        char m_data;
        std::vector<Node> m_children;
        bool m_isLeaf;
    };
    /* -------------------------------- */

    /* members */
    std::shared_ptr<Node> m_root;
};