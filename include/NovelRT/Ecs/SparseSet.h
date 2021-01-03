// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SPARSESET_H
#define NOVELRT_ECS_SPARSESET_H

#include "EcsUtils.h"
#include "../Atom.h"
#include <unordered_map>
#include <memory>
#include <iterator>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include "../Exceptions/DuplicateKeyException.h"

namespace NovelRT::Ecs
{
    /**
     * @brief A custom sparse set implementation designed at storing small, blittable types.
     * 
     * Please note that this storage type assumes that the component in question is a simple struct at all times.
     * The value type should not be massively complex as there may be many copy instructions that are not SIMDifiable if the type is too complicated.
     * 
     * @tparam TKey The type to use for the Key.
     * @tparam TValue The type to use for the value.
     * @tparam THashFunction An optional custom hashing function should your key type require one.
     */
    template <typename TKey, typename TValue, typename THashFunction = std::hash<TKey>>
    class SparseSet
    {
        private:
        std::vector<TKey> _sparseBlock;
        std::vector<TValue> _denseBlock;
        std::unordered_map<TKey, size_t, THashFunction> _sparseMap;

        public:
        /**
         * @brief A non const iterator for traversing the keys and values of this particular SparseSet as tuple pairs.
         * 
         */
        class Iterator
        {
            public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<TKey, TValue>;
            using pointer = std::tuple<typename std::vector<TKey>::iterator, typename std::vector<TValue>::iterator>;
            using reference = std::tuple<TKey&, TValue&>;

            private:
            pointer _ptr;

            public:
            Iterator(pointer ptr) : _ptr(ptr) {}

            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), *std::get<1>(_ptr));
            }

            pointer operator->()
            {
                return _ptr;
            }

            Iterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr)++;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        /**
         * @brief A const iterator for traversing the keys and values of this particular SparseSet as tuple pairs in a read-only fashion.
         * 
         */
        class ConstIterator
        {
            public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<TKey, TValue>;
            using pointer = std::tuple<typename std::vector<TKey>::const_iterator, typename std::vector<TValue>::const_iterator>;
            using reference = std::tuple<const TKey&, const TValue&>;
        
            private:
            pointer _ptr;
        
            public:
            ConstIterator(pointer ptr) : _ptr(ptr) {}
        
            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), *std::get<1>(_ptr));
            }
        
            const ConstIterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr)++;
                return *this;
            }
        
            ConstIterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
        
            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
        
            friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        /**
         * @brief Constructs a new instance of SparseSet with the given type parameters.
         * 
         */
        SparseSet() noexcept : _sparseBlock(std::vector<TKey>()), _denseBlock(std::vector<TValue>()), _sparseMap(std::unordered_map<TKey, size_t, THashFunction>())
        {
        }

        /**
         * @brief Inserts a new key with paired with an initial value into the set. All keys must be unique.
         * 
         * @param key The new key to insert.
         * @param value The initial value to associate with the key.
         * 
         * @exception Exceptions::DuplicateKeyException when a duplicate key is provided.
         */
        void Insert(TKey key, TValue value)
        {
            if (ContainsKey(key))
            {
                throw Exceptions::DuplicateKeyException();
            }

            _denseBlock.push_back(value);
            _sparseBlock.push_back(key);
            _sparseMap.emplace(key, _denseBlock.size() - 1);
        }

        /**
         * @brief Removes a given key and its associated value from the set.
         * 
         * @param key The key to remove.
         * 
         * @exception std::out_of_range if the key is not present within the SparseSet.
         */
        void Remove(TKey key)
        {
            size_t arrayIndex = _sparseMap.at(key);
            _denseBlock.erase(_denseBlock.begin() + arrayIndex);
            _sparseBlock.erase(_sparseBlock.begin() + arrayIndex);
            _sparseMap.erase(key);

            for (auto &i : _sparseMap)
            {
                if (i.second < arrayIndex)
                {
                    continue;
                }

                i.second -= 1;
            }
        }

        /**
         * @brief Attempts to remove the given key from the SparseSet with additional safety checks to ensure it is an exceptionless operation.
         * 
         * @param key The key to remove.
         * @return true if the key was successfully removed.
         * @return false if SparseSet::ContainsKey returns false.
         */
        bool TryRemove(TKey key) noexcept
        {
            if (ContainsKey(key))
            {
                Remove(key);
                return true;
            }
            
            return false;
        }

        /**
         * @brief Erases all data from the SparseSet.
         * 
         */
        void Clear() noexcept
        {
            _sparseBlock.clear();
            _denseBlock.clear();
            _sparseMap.clear();
        }

        /**
         * @brief Checks if the key is present within the SparseSet.
         * 
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @param key The key to look for.
         * @return true if the key is present.
         * @return false if the key was not found.
         */
        [[nodiscard]] bool ContainsKey(TKey key) const noexcept
        {
            return std::find(_sparseBlock.begin(), _sparseBlock.end(), key) != _sparseBlock.end();
        }

        /**
         * @brief Copies the key out of the sparse set at the given dense index.
         * 
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @param denseIndex The location in the dense data to copy from.
         * @return TKey The key at the specified dense location.
         * 
         * @exception std::out_of_range if the specified dense index does not exist within the SparseSet.
         */
        [[nodiscard]] TKey CopyKeyBasedOnDenseIndex(size_t denseIndex) const
        {
            return _sparseBlock.at(denseIndex);
        }

        /**
         * @brief Copies the value out of the sparse set at the given dense index.
         * 
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @param denseIndex The location in the dense data to copy from.
         * @return TValue The value at the specified dense location.
         * 
         * @exception std::out_of_range if the specified dense index does not exist within the SparseSet.
         */
        [[nodiscard]] TValue CopyValueBasedOnDenseIndex(size_t denseIndex) const
        {
            return _denseBlock.at(denseIndex);
        }

        /**
         * @brief Gets the current length of the SparseSet.
         * 
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return size_t 
         */
        [[nodiscard]] size_t Length() const noexcept
        {
            return _sparseBlock.size();
        }

        /**
         * @brief Fetches the value associated with the provided key.
         * 
         * @param key The target key to search for.
         * @return TValue& The value as a mutable reference.
         * 
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @exception std::out_of_range if the specified key does not exist within the SparseSet.
         */
        [[nodiscard]] TValue& operator[](TKey key)
        {
            return _denseBlock.at(_sparseMap.at(key));
        }

        /**
         * @brief Fetches the value associated with the provided key.
         * 
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @param key The target key to search for.
         * @return TValue& The value as a const reference.
         * 
         * @exception std::out_of_range if the specified key does not exist within the SparseSet.
         */
        [[nodiscard]] const TValue& operator[](TKey key) const
        {
            return _denseBlock.at(_sparseMap.at(key));
        }

        // clang-format off

        /**
         * @brief Gets the beginning forward iterator state for this SparseSet.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::Iterator starting at the beginning.
         */
        [[nodiscard]] auto begin() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock.begin(), _denseBlock.begin()));
        }

        /**
         * @brief Gets the ending forward iterator state for this SparseSet.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::Iterator starting at the end.
         */
        [[nodiscard]] auto end() noexcept
        {
            return Iterator(std::make_tuple(_sparseBlock.end(), _denseBlock.end()));
        }

        /**
         * @brief Gets the beginning forward const iterator state for this SparseSet.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] auto cbegin() const noexcept
        {
            return ConstIterator(std::make_tuple(_sparseBlock.cbegin(), _denseBlock.cbegin()));
        }

        /**
         * @brief Gets the ending forward const iterator state for this SparseSet.
         * 
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for calling a method.
         * 
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] auto cend() const noexcept
        {
            return ConstIterator(std::make_tuple(_sparseBlock.cend(), _denseBlock.cend()));
        }

        // clang-format on
    };
} // namespace NovelRT::Ecs

#endif //!NOVELRT_ECS_SPARSESET_H
