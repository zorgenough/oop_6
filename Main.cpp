#include <iostream> 
#include <algorithm> 
#include <list> 
#include <Windows.h> 
 
template <typename T> 
class GroupList { 
private: 
 std::list<T> m_data; 
 
public: 
 void addGroup(typename std::list<T>::iterator it, std::list<T> group); 
 void removeGroup(typename std::list<T>::iterator begin, typename std::list<T>::iterator end); 
 void replaceGroup(typename std::list<T>::iterator begin, typename std::list<T>::iterator end, std::list<T> group); 
 typename std::list<T>::iterator find(T value); 
 std::list<typename std::list<T>::iterator> findGroup(std::list<T>& group); 
 GroupList<T> unionWith(GroupList<T>& other); 
 GroupList<T> intersectionWith(GroupList<T>& other); 
 void print(); 
 void read(); 
 typename std::list<T>::iterator begin(); 
 typename std::list<T>::iterator end(); 
};
 
template <typename T> 
void GroupList<T>::addGroup(typename std::list<T>::iterator it, std::list<T> group) { 
 m_data.splice(it, group); 
}
 
template <typename T>
void GroupList<T>::removeGroup(typename std::list<T>::iterator begin, typename std::list<T>::iterator end) { 
 m_data.erase(begin, end); 
}
 
template <typename T>
void GroupList<T>::replaceGroup(typename std::list<T>::iterator begin, typename std::list<T>::iterator end, std::list<T> group) { 
 m_data.splice(begin, group); 
    m_data.erase(begin, end);
}
 
template <typename T>
typename std::list<T>::iterator GroupList<T>::find(T value) {
    return std::find(m_data.begin(), m_data.end(), value);
}
 
template <typename T>
std::list<typename std::list<T>::iterator> GroupList<T>::findGroup(std::list<T>& group) {
    std::list<typename std::list<T>::iterator> result;
    for (auto it = m_data.begin(); it != m_data.end(); ++it) {
        auto sub_it = it;
        auto group_it = group.begin();
        while (sub_it != m_data.end() && group_it != group.end() && *sub_it == *group_it) {
            ++sub_it;
            ++group_it;
        }
        if (group_it == group.end()) {
            result.push_back(it);
        }
    }
    return result;
}
 
template <typename T>
GroupList<T> GroupList<T>::unionWith(GroupList<T>& other){
    GroupList<T> result(*this);
    for (const auto& value : other.m_data) {
        if (std::find(result.m_data.begin(), result.m_data.end(), value) == result.m_data.end()) {
            result.m_data.push_back(value);
        }
    }
    return result;
}
 
template <typename T>
GroupList<T> GroupList<T>::intersectionWith(GroupList<T>& other){
    GroupList<T> result;
    for (const auto& value : m_data) {
        if (std::find(other.m_data.begin(), other.m_data.end(), value) != other.m_data.end()) {
            result.m_data.push_back(value);
        }
    }
    return result;
}
 
template <typename T>
void GroupList<T>::read() {
    size_t size;
    std::cout << "Введите размер списка: ";
    std::cin >> size;
    m_data.resize(size);
    std::cout << "Введите элементы списка: ";
    for (auto& value : m_data) {
        std::cin >> value;
    }
}
 
template <typename T>
void GroupList<T>::print() {
    std::cout << "Список: ";
    for (auto& value : m_data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}
 
template <typename T>
typename std::list<T>::iterator GroupList<T>::begin() {
    return m_data.begin();
}
 
template <typename T>
typename std::list<T>::iterator GroupList<T>::end() {
    return m_data.end();
}
 
int main() {
    GroupList<int> list1;
    list1.read();
 
    std::list<int> add_group = { 2, 3, 4 };
    list1.addGroup(list1.begin(), add_group);
    list1.print();
    std::list<int> repl_group = {10, 11, 12};
    list1.replaceGroup(list1.begin(), list1.find(4), repl_group);
    list1.print();
 
    GroupList<int> list2;
    list2.read();
 
    GroupList<int> intersection = list1.intersectionWith(list2);
    GroupList<int> union_ = list1.unionWith(list2);
 
    intersection.print();
    union_.print();
}
