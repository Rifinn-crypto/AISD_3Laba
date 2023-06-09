#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <limits>
#include <unordered_map>
//#include "Graphs.h"

// шаблонный класс графа
template<typename Vertex, typename Distance = double>
class Graph {
private:
    struct Edge {
        Vertex from; // откуда идет
        Vertex to; // куда идет
        Distance distance;
        Edge(int from, int to, Distance distance) : from(from), to(to), distance(distance) {}
        Edge() = default;
    };
    std::unordered_map<Vertex, std::vector<Edge>> _data; // вершины + список ребер
public:
    bool has_vertex(const Vertex& v) const {
        /*
         * метод наличия вершины в графе
         * v - вершина, которую нужно найти
         * .count() - возвращает кол-во элементов с сравн.ключом
         */
        return _data.count(v) > 0;
    }

    void add_vertex(const Vertex& v) {
        /*
         * метод добавления новой вершины в граф
         * v - вершина, которую нужно добавить
         */
        if (has_vertex(v))
            /*setlocale(0, "");*/
            throw std::invalid_argument("Вершина уже существует!");
        _data[v] = std::vector<Edge>();
    }

    bool remove_vertex(const Vertex& v) {
        /*
         * метод удаления вершины из графа
         * v - вершина, которую нужно удалить
         * [&] - захват по ссылке ребра, pred - предикат для поиска ребра
         * find_if ищет элемент, для которого предикат возвращает true
         */
        if (!has_vertex(v))
            return false;
        for (auto& pair : _data) {
            auto pred = [&v](const auto& edge) {
                return edge.to == v;
            };
            auto vector_iter = std::find_if(pair.second.begin(), pair.second.end(), pred);
            while (vector_iter != pair.second.end()) {
                auto tmp_begin = pair.second.erase(vector_iter);
                vector_iter = std::find_if(tmp_begin, pair.second.end(), pred);
            }
        }
        return true;
    }

    std::vector<Vertex> vertices() const {
        /*
         * метод получения всех вершин графа
         * возращаемый элемент - вектор вершин
         */
        std::vector<Vertex> result;
        for (auto& item : _data)
            result.push_back(item.first);
        return result;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        /*
         * метод добавления ребра в граф
         * from - откуда идет, to - куда идет, d - вес ребра
         */
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("Нет вершины from или to!");
        _data[from].push_back(Edge(from, to, d));
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        /*
         * метод удаления ребра из графа
         * from - откуда идет, to - куда идет
         * [&] - захват по ссылке ребра, pred - предикат для поиска ребра
         * find_if ищет элемент, для которого предикат возвращает true
         */
        if (!has_vertex(from) || !has_vertex(to))
            return false;
        bool is_removed = false;
        auto pred = [&from, &to](const auto& edge) {
            return edge.from == from && edge.to == to;
        };
        auto vector_iter = std::find_if(_data.at(from).begin(), _data.at(from).end(), pred);
        while (vector_iter != _data.at(from).end()) {
            vector_iter = std::find_if(_data.at(from).erase(vector_iter), _data.at(from).end(), pred);
            is_removed = true;
        }
        return is_removed;
    }

    bool remove_edge(const Edge& e) {
        /*
         * метод удаления ребра из графа
         * e - ребро, которое нужно удалить
         * pred - предикат
         */
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        auto pred = [&e](const auto& edge) {
            return edge.from == e.from && edge.to == e.to && edge.distance == e.distance;
        };
        bool is_removed = false;
        auto vector_iter = std::find_if(_data.at(e.from).begin(), _data.at(e.from).end(), pred);
        while (vector_iter != _data.at(e.from).end()) {
            vector_iter = std::find_if(_data.at(e.from).erase(vector_iter), _data.at(e.from).end(), pred);
            is_removed = true;
        }
        return is_removed;
    }

    void generate_random_graph(size_t count) {
        /*
         * метод генерации случайного графа
         * count - кол-во вершин в графе
         * n - кол-во ребер в графе
         */
        for (size_t i = 0; i < count; i++)
            add_vertex(i);
        for (size_t i = 0; i < count; i++) {
            auto n = rand() % count;
            for (size_t j = 0; j < n; j++)
                if (i != j)
                    add_edge(i, j, rand() % 100);
        }

    }

    void print() const {
        /*
         * метод вывода графа в консоль
         * вершины и ребра
         */
        std::cout << "Вершины: ";
        for (auto& item : _data)
            std::cout << item.first << " ";
        std::cout << std::endl;
        std::cout << "Ребра: " << std::endl;
        for (auto& item : _data)
            for (auto& item2 : item.second)
                std::cout << item2.from << " -> " << item2.to << " (" << item2.distance << ")" << std::endl;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        /*
         * метод проверки наличия ребра в графе
         * from - откуда идет, to - куда идет
         * _data.at(from) - вектор ребер, выходящих из вершины from
         */
        if (!has_vertex(from) || !has_vertex(to))
            return false;
        for (auto& item : _data.at(from))
            if (item.to == to)
                return true;
        return false;
    }

    bool has_edge(const Edge& e) const {
        /*
         * метод проверки наличия ребра в графе
         * e - ребро, которое нужно проверить
         * _data.at(e.from) - вектор ребер, выходящих из вершины e.from
         */
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        for (auto& item : _data.at(e.from))
            if (item.to == e.to)
                return true;
        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex) const {
        /*
         * метод получения всех ребер выходящих из вершины
         * vertex - вершина, из которой идут ребра
         */
        if (!has_vertex(vertex))
            throw std::invalid_argument("Нет вершины vertex!");
        return _data.at(vertex);
    }

    size_t order() const {
        /*
         * метод получения порядка графа (количество вершин)
         */
        return _data.size();
    }

    size_t degree() const {
        /*
         * метод получения степени графа (максимальная степень вершины)
         */
        size_t result = 0;
        for (const auto& pair : _data) {
            size_t cur_degree = pair.second.size();
            if (cur_degree > result)
                result = cur_degree;
        }
        return result;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to, Distance* dist = nullptr) const {
        /*
         * метод поиска кратчайшего пути по алгоритму Беллмана-Форда
         * from - откуда идет, to - куда идет
         * dist - расстояние от from до to
         * result - результирующий путь
         * distance - расстояния от from до всех остальных вершин
         * ancestors - предки всех вершин
         * order() - количество вершин в графе
         */
        if (!has_vertex(from) || !has_vertex(to))
            throw std::invalid_argument("Вершина не найдена!");
        std::vector<Edge> result;
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Edge> ancestors;
        for (auto& item : _data)
            distance[item.first] = std::numeric_limits<Distance>::max();
        distance[from] = 0;
        // алгоритм Беллмана-Форда (поиск кратчайшего пути)
        for (size_t i = 0; i < order() - 1; ++i) {
            for (const auto& pair : _data) {
                for (const auto& edge : pair.second) {
                    if (distance[edge.from] + edge.distance < distance[edge.to]) {
                        distance[edge.to] = distance[edge.from] + edge.distance;
                        ancestors[edge.to] = edge;
                    }
                }
            }
        }
        // проверка на отрицательный цикл
        for (const auto& pair : _data)
            for (const auto& edge : pair.second)
                if (distance[edge.from] + edge.distance < distance[edge.to])
                    throw std::runtime_error("Граф имеет отрицательный цикл");
        // если путь не найден (расстояние до вершины равно максимальному значению - бесконечности)
        if (distance[to] == std::numeric_limits<Distance>::max()) {
            *dist = std::numeric_limits<Distance>::max();
            return {};
        }
        // восстановление пути (поиск предков)
        Vertex current = to; // текущая вершина - конечная
        while (current != from) {
            result.push_back(ancestors[current]);
            current = ancestors[current].from;
        }
        if (dist != nullptr)
            *dist = distance[to];
        // разворачиваем путь (т.к. мы восстанавливали его с конца)
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        /*
         * метод обхода графа в глубину
         * start_vertex - вершина, с которой начинается обход
         * visited - список посещенных вершин
         * stack - стек вершин, которые нужно посетить
         * edges - список смежных вершин
         */
        if (!has_vertex(start_vertex))
            throw std::invalid_argument("Стартовая вершина не найдена!");
        std::vector<Vertex> visited;
        std::stack<Vertex> stack;
        visited.push_back(start_vertex);
        stack.push(start_vertex);
        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();
            for (const auto& edge : _data.at(current)) {
                if (std::find(visited.begin(), visited.end(), edge.to) == visited.end()) {
                    visited.push_back(edge.to);
                    stack.push(edge.to);
                }
            }
        }
        return visited;
    }
};
