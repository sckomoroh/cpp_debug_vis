#pragma once

#include <functional>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <json11.hpp>

#include "common.h"

using namespace std;

using JObject = json11::Json::object;
using JArray = json11::Json::array;

string to_string(const char& ch) { return string() + ch; }

string to_string(const string& s) { return s; }

string to_string(ListNode* n)
{
    if (n == nullptr) {
        return "nullptr";
    }

    ostringstream oss;
    oss << n;
    return oss.str();
}

string to_string(TreeNode* n)
{
    ostringstream oss;
    oss << n;
    return oss.str();
}

template <class T>
class VectorViz {
private:
    vector<T>& data;
    std::function<string(T)> print;

public:
    VectorViz(vector<T>& data, std::function<string(T)> print = {})
        : data{data}
        , print{print}
    {
    }

public:
    virtual string vis()
    {
        auto grid = JObject{{"grid", true}};
        auto columnsArray = JArray{};
        for (auto& item : data) {
            if (print) {
                columnsArray.push_back(JObject{{"tag", print(item)}});
            }
            else {
                columnsArray.push_back(JObject{{"tag", to_string(item)}});
            }
        }
        auto columns = JObject{{"columns", columnsArray}};

        auto root = json11::Json{JObject{{"kind", grid}, {"rows", JArray{{columns}}}}};

        return root.dump();
    }
};

template <class T, class V>
class MapViz {
private:
    unordered_map<T, V>& data;
    std::function<string(T)> print;

public:
    MapViz(unordered_map<T, V>& data)
        : data{data}
    {
    }

public:
    virtual string vis()
    {
        auto grid = JObject{{"grid", true}};
        auto columnsArray1 = JArray{};
        for (auto& item : data) {
            columnsArray1.push_back(JObject{{"tag", to_string(item.first)}});
        }

        auto columnsArray2 = JArray{};
        for (auto& item : data) {
            columnsArray2.push_back(JObject{{"tag", to_string(item.second)}});
        }

        auto columns1 = JObject{{"columns", columnsArray1}};
        auto columns2 = JObject{{"columns", columnsArray2}};

        auto root = json11::Json{JObject{{"kind", grid}, {"rows", JArray{{columns1, columns2}}}}};

        return root.dump();
    }
};

template <class T>
class SetViz {
private:
    unordered_set<T>& data;

public:
    SetViz(unordered_set<T>& data)
        : data{data}
    {
    }

public:
    virtual string vis()
    {
        auto grid = JObject{{"grid", true}};
        auto columnsArray = JArray{};
        for (auto& item : data) {
            columnsArray.push_back(JObject{{"tag", to_string(item)}});
        }
        auto columns = JObject{{"columns", columnsArray}};

        auto root = json11::Json{JObject{{"kind", grid}, {"rows", JArray{{columns}}}}};

        return root.dump();
    }
};

template <class T>
class StackViz {
private:
    stack<T>& data;
    std::function<string(T)> print;

public:
    StackViz(stack<T>& data, std::function<string(T)> print = {})
        : data{data}
        , print{print}
    {
    }

public:
    virtual string vis()
    {
        auto grid = JObject{{"grid", true}};
        auto columnsArray = JArray{};
        stack<T> stack = data;
        while (!stack.empty()) {
            if (print) {
                columnsArray.push_back(JObject{{"tag", print(stack.top())}});
            }
            else {
                columnsArray.push_back(JObject{{"tag", to_string(stack.top())}});
            }
            stack.pop();
        }
        auto columns = JObject{{"columns", columnsArray}};

        auto root = json11::Json{JObject{{"kind", grid}, {"rows", JArray{{columns}}}}};

        return root.dump();
    }
};

template <class T>
class QueueViz {
private:
    queue<T>& data;
    std::function<string(T)> print;

public:
    QueueViz(queue<T>& data, std::function<string(T)> print = {})
        : data{data}
        , print{print}
    {
    }

public:
    virtual string vis()
    {
        auto grid = JObject{{"grid", true}};
        auto columnsArray = JArray{};
        queue<T> stack = data;
        while (!stack.empty()) {
            if (print) {
                columnsArray.push_back(JObject{{"tag", print(stack.front())}});
            }
            else {
                columnsArray.push_back(JObject{{"tag", to_string(stack.front())}});
            }
            stack.pop();
        }
        auto columns = JObject{{"columns", columnsArray}};

        auto root = json11::Json{JObject{{"kind", grid}, {"rows", JArray{{columns}}}}};

        return root.dump();
    }
};

class ListViz {
public:
    vector<ListNode*> nodes;
    unordered_map<ListNode**, string> pointers;

public:
    ListViz(ListNode* head, unordered_map<ListNode**, string> pointers = {})
        : pointers{pointers}
    {
        ListNode* node = head;
        while (node != nullptr) {
            nodes.push_back(node);
            node = node->next;
        }
    }

public:
    virtual string vis()
    {
        auto graph = JObject{{"graph", true}};
        auto nodesArray = JArray();
        for (auto node : nodes) {
            nodesArray.push_back(JObject{{"id", to_string(node)}, {"label", to_string(node->val)}});
        }

        for (auto kv : pointers) {
            nodesArray.push_back(JObject{
                {"id", to_string(kv.second)}, {"label", to_string(kv.second)}, {"color", "red"}});
        }

        auto edgesArray = JArray();
        for (auto node : nodes) {
            if (node->next != nullptr) {
                edgesArray.push_back(
                    JObject{{"from", to_string(node)}, {"to", to_string(node->next)}});
            }
        }

        for (auto kv : pointers) {
            if (kv.first != nullptr) {
                edgesArray.push_back(JObject{{"from", to_string(kv.second)},
                                             {"to", to_string(*kv.first)},
                                             {"color", "red"}});
            }
        }

        auto root =
            json11::Json{JObject{{"kind", graph}, {"nodes", nodesArray}, {"edges", edgesArray}}};

        return root.dump();
    }
};

class TreeViz {
private:
    vector<TreeNode*> nodes;
    unordered_map<TreeNode**, string> pointers;

public:
    TreeViz(TreeNode* root, unordered_map<TreeNode**, string> pointers = {})
        : pointers{pointers}
    {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* node;

        while (!q.empty()) {
            node = q.front();
            q.pop();
            if (node == nullptr) {
                continue;
            }

            nodes.push_back(node);
            q.push(node->left);
            q.push(node->right);
        }
    }

public:
    virtual string vis()
    {
        auto graph = JObject{{"graph", true}};
        auto nodesArray = JArray();

        for (auto node : nodes) {
            nodesArray.push_back(JObject{{"id", to_string(node)}, {"label", to_string(node->val)}});
        }

        for (auto kv : pointers) {
            nodesArray.push_back(JObject{
                {"id", to_string(kv.second)}, {"label", to_string(kv.second)}, {"color", "red"}});
        }

        auto edgesArray = JArray();
        for (auto node : nodes) {
            if (node->left != nullptr) {
                edgesArray.push_back(
                    JObject{{"from", to_string(node)}, {"to", to_string(node->left)}});
            }

            if (node->right != nullptr) {
                edgesArray.push_back(
                    JObject{{"from", to_string(node)}, {"to", to_string(node->right)}});
            }
        }

        for (auto kv : pointers) {
            if (kv.first != nullptr) {
                edgesArray.push_back(JObject{{"from", to_string(kv.second)},
                                             {"to", to_string(*kv.first)},
                                             {"color", "red"}});
            }
        }

        auto root =
            json11::Json{JObject{{"kind", graph}, {"nodes", nodesArray}, {"edges", edgesArray}}};

        return root.dump();
    }
};
