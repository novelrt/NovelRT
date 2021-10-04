// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SCENEGRAPH_SCENENODE_H
#define NOVELRT_SCENEGRAPH_SCENENODE_H

#ifndef NOVELRT_SCENEGRAPH_H
#error NovelRT does not support including types explicitly by default. Please include SceneGraph.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::SceneGraph
{
    class SceneNode : public std::enable_shared_from_this<SceneNode>
    {
    public:
        template<typename T> class breadth_first_traversal_result_iterator;
        template<typename T> class depth_first_traversal_result_iterator;

    private:
        std::set<std::shared_ptr<SceneNode>> _parents;
        std::set<std::shared_ptr<SceneNode>> _children;

    public:
        const std::set<std::shared_ptr<SceneNode>>& getChildren() const noexcept
        {
            return _children;
        }

        const std::set<std::shared_ptr<SceneNode>>& getParents() const noexcept
        {
            return _parents;
        }

        bool insert(const std::shared_ptr<SceneNode>& node)
        {
            node->_parents.insert(shared_from_this());
            return _children.insert(node).second;
        }

        bool remove(const std::shared_ptr<SceneNode>& node)
        {
            auto numErased = _children.erase(node);
            numErased += node->_parents.erase(shared_from_this());

            assert((numErased == 0) || (numErased == 2));
            return numErased != 0;
        }

        bool isAdjacent(const std::shared_ptr<SceneNode>& node)
        {
            return _children.find(node) != _children.cend() || _parents.find(node) != _parents.cend();
        }

        void traverseBreadthFirst(std::function<void(const std::shared_ptr<SceneNode>&)> action)
        {
            // We do a breadth-first traversal of the nodes using a queue-based algorithm
            // to track pending nodes, rather than using recursion, so that we can
            // process much more complex graphs.

            auto visitedNodes = std::set<std::shared_ptr<SceneNode>>();
            auto pendingNodes = std::queue<std::shared_ptr<SceneNode>>();

            visitedNodes.insert(shared_from_this());
            pendingNodes.push(shared_from_this());

            do
            {
                auto node = pendingNodes.front();
                action(node);
                pendingNodes.pop();

                for (auto child : node->getChildren())
                {
                    if (visitedNodes.find(child) == visitedNodes.cend())
                    {
                        visitedNodes.insert(child);
                        pendingNodes.push(child);
                    }
                }

            } while (!pendingNodes.empty());
        }

        void traverseDepthFirst(std::function<void(const std::shared_ptr<SceneNode>&)> action)
        {
            // We do a depth-first traversal of the nodes using a stack-based algorithm
            // to track pending nodes, rather than using recursion, so that we can
            // process much more complex graphs

            auto visitedNodes = std::set<std::shared_ptr<SceneNode>>();
            auto pendingNodes = std::stack<std::shared_ptr<SceneNode>>();

            visitedNodes.insert(shared_from_this());
            pendingNodes.push(shared_from_this());

            do
            {
                auto node = pendingNodes.top();
                action(node);
                pendingNodes.pop();

                for (auto child : node->getChildren())
                {
                    if (visitedNodes.find(child) == visitedNodes.cend())
                    {
                        visitedNodes.insert(child);
                        pendingNodes.push(child);
                    }
                }

            } while (!pendingNodes.empty());
        }

        template<typename T>
        breadth_first_traversal_result_iterator<T> traverseBreadthFirst(
            std::function<T(const std::shared_ptr<SceneNode>&)> function)
        {
            return breadth_first_traversal_result_iterator<T>(shared_from_this(), function);
        }

        template<typename T>
        depth_first_traversal_result_iterator<T> traverseDepthFirst(
            std::function<T(const std::shared_ptr<SceneNode>&)> function)
        {
            return depth_first_traversal_result_iterator<T>(shared_from_this(), function);
        }

        bool canReach(const std::shared_ptr<SceneNode>& node)
        {
            auto result = traverseDepthFirst<bool>(
                [&](const std::shared_ptr<SceneNode>& traversedNode) { return traversedNode == node; });

            while ((*result != true) && !result.isEnd())
            {
                ++result;
            }

            return *result;
        }

        template<typename T> class breadth_first_traversal_result_iterator
        {
        private:
            std::function<T(const std::shared_ptr<SceneNode>&)> _function;
            std::queue<std::shared_ptr<SceneNode>> _pendingNodes;
            std::set<std::shared_ptr<SceneNode>> _visitedNodes;

            T _value;

        public:
            using iterator_category = std::output_iterator_tag;
            using value_type = T;
            using pointer = value_type*;
            using const_pointer = const value_type*;
            using reference = value_type&;
            using const_reference = const value_type&;

            breadth_first_traversal_result_iterator(const std::shared_ptr<SceneNode>& node,
                                                    std::function<T(const std::shared_ptr<SceneNode>&)> function)
                : _function(function)
            {
                _pendingNodes.push(node);
                _visitedNodes.insert(node);
                ++*this;
            }

            const_reference operator*() const noexcept
            {
                return _value;
            }

            const_pointer operator->() const noexcept
            {
                return std::pointer_traits<pointer>::pointer_to(**this);
            }

            breadth_first_traversal_result_iterator& operator++()
            {
                auto node = _pendingNodes.front();
                _value = _function(node);
                _pendingNodes.pop();

                for (auto child : node->getChildren())
                {
                    if (_visitedNodes.find(child) == _visitedNodes.cend())
                    {
                        _visitedNodes.insert(child);
                        _pendingNodes.push(child);
                    }
                }

                return *this;
            }

            breadth_first_traversal_result_iterator operator++(int32_t) noexcept
            {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const breadth_first_traversal_result_iterator& other) const noexcept
            {
                return _value == other._value && (_pendingNodes.empty() == other._pendingNodes.empty() ||
                                                  _pendingNodes.front() == other._pendingNodes.front());
            }

            bool operator!=(const breadth_first_traversal_result_iterator& other) const noexcept
            {
                return !(*this == other);
            }

            bool isEnd() const noexcept
            {
                return _pendingNodes.empty();
            }
        };

        template<typename T> class depth_first_traversal_result_iterator
        {
        private:
            std::function<T(const std::shared_ptr<SceneNode>&)> _function;
            std::stack<std::shared_ptr<SceneNode>> _pendingNodes;
            std::set<std::shared_ptr<SceneNode>> _visitedNodes;

            T _value;

        public:
            using iterator_category = std::output_iterator_tag;
            using value_type = T;
            using pointer = value_type*;
            using const_pointer = const value_type*;
            using reference = value_type&;
            using const_reference = const value_type&;

            depth_first_traversal_result_iterator(const std::shared_ptr<SceneNode>& node,
                                                  std::function<T(const std::shared_ptr<SceneNode>&)> function)
                : _function(function)
            {
                _pendingNodes.push(node);
                _visitedNodes.insert(node);
                ++*this;
            }

            const_reference operator*() const noexcept
            {
                return _value;
            }

            const_pointer operator->() const noexcept
            {
                return std::pointer_traits<pointer>::pointer_to(**this);
            }

            depth_first_traversal_result_iterator& operator++()
            {
                auto node = _pendingNodes.top();
                _value = _function(node);
                _pendingNodes.pop();

                for (auto child : node->getChildren())
                {
                    if (_visitedNodes.find(child) == _visitedNodes.cend())
                    {
                        _visitedNodes.insert(child);
                        _pendingNodes.push(child);
                    }
                }

                return *this;
            }

            depth_first_traversal_result_iterator operator++(int32_t) noexcept
            {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const depth_first_traversal_result_iterator& other) const noexcept
            {
                return _value == other._value && (_pendingNodes.empty() == other._pendingNodes.empty() ||
                                                  _pendingNodes.top() == other._pendingNodes.top());
            }

            bool operator!=(const depth_first_traversal_result_iterator& other) const noexcept
            {
                return !(*this == other);
            }

            bool isEnd() const noexcept
            {
                return _pendingNodes.empty();
            }
        };
    };
}

#endif
