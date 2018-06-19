
#ifndef __borc_treenode_hpp__
#define __borc_treenode_hpp__

#include <memory>
#include <list>
#include <algorithm>

namespace borc {
    template<typename T>
    class TreeNode final {
    public:
        typedef typename std::list<std::unique_ptr<TreeNode<T>>>::iterator iterator;

    public:
        TreeNode() {}

        TreeNode(std::unique_ptr<T> data) {
            this->setData(std::move(data));
        }

        T* getData() const {
            return m_data.get();
        }
        
        TreeNode* setData(std::unique_ptr<T> data) {
            m_data = std::move(data);

            return this;
        }

        TreeNode<T>* createChild() {
            return this->createChild(std::unique_ptr<T>());
        }

        TreeNode<T>* createChild(std::unique_ptr<T> data) {
            auto child = new TreeNode<T>(std::move(data));

            m_childs.emplace_back(child);

            return child;
        }

        TreeNode<T>* insertChild(std::unique_ptr<TreeNode<T>> childPtr) {
            auto child = childPtr.get();

            m_childs.push_back(std::move(childPtr));

            return child;
        }

        friend auto begin(TreeNode<T> *node) {
            return node->begin();
        }

        friend auto end(TreeNode<T> *node) {
            return node->end();
        }

        iterator begin() {
            return m_childs.begin();
        }

        iterator end() {
            return m_childs.end();
        }

    public:
        static std::unique_ptr<TreeNode<T>> create() {
            return std::make_unique<TreeNode<T>>();
        }

        static std::unique_ptr<TreeNode<T>> create(std::unique_ptr<T> data) {
            return std::make_unique<TreeNode<T>>(std::move(data));
        }

    private:
        std::unique_ptr<T> m_data;
        std::list<std::unique_ptr<TreeNode<T>>> m_childs;
    };
}

#endif
