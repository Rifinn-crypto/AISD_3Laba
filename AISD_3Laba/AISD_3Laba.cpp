#include "Graphs.h"

/* Задача 2. Пусть дан связный граф, в котором узлы – это торговые точки.
 * Необходимо превратить одну из торговых точек в склад. Цена доставки от склада в точку зависит
 * от расстояния. Найдите оптимальную с точки зрения максимальных затрат точку
 * (т.е. точку, для которой максимальное расстояние до любой другой точки минимально).
 */
template<typename Vertex, typename Distance = double>
Vertex find_optimal(const Graph<Vertex, Distance>& graph) {
    /*
     * метод для поиска оптимальной вершины графа (т.е. вершины, для которой максимальное расстояние до любой другой вершины минимально)
     * graph - граф
     * distance_vertex - словарь вершин и расстояний
     */
    if (graph.order() == 0)
        throw std::invalid_argument("Ошибка! Пустой граф не имеет центра.\n");
    Distance min_distance = std::numeric_limits<Distance>::max();
    Vertex min_vertex = 0;
    for (auto& item_i : graph.vertices()) {
        Distance d = 0;
        for (auto& item_j : graph.vertices()) {
            Distance current_distance = 0;
            graph.shortest_path(item_i, item_j, &current_distance);
            // если путь не сущ-т, то -> расстояние до этой вершины бесконечность
            if (current_distance == std::numeric_limits<Distance>::max() || d == std::numeric_limits<Distance>::max())
                d = std::numeric_limits<Distance>::max();
            else
                if (d < current_distance)
                    d = current_distance;
        }
        if (d < min_distance) {
            min_distance = d;
            min_vertex = item_i;
        }
    }
    return min_vertex;
}

void text_menu1() {
    /*
     * главное меню
     */
    setlocale(0, "");
    std::cout << "\n[1] Создать случайный граф\n"
        << "[2] Вывод графа\n"
        << "[3] Поиск кратчайшего пути (Беллман-Форд)\n"
        << "[4] Обход в глубину\n"
        << "[5] Задача(2)\n"
        << "[6] Конфигурация графа\n"
        << "[7] Тестовый граф\n"
        << "[0] Выход\n"
        << "--> ";
}

void text_menu2() {
    /*
     * меню (конфигурация графа)
     */
    setlocale(0, "");
    std::cout << "\n[1] Добавить ребро/вершину\n"
        << "[2] Проверить ребро/вершину\n"
        << "[3] Удалить ребро/вершину\n"
        << "[4] Получить все ребра, выходящих из вершины\n"
        << "[5] Порядок графа\n"
        << "[6] Степень графа\n"
        << "[0] Назад в главное меню\n"
        << "--> ";
}

int main() {
    Graph<int, double> graph;
    while (true) {
        text_menu1();
        int command;
        std::cin >> command;
        switch (command) {
        case 1:
        {
            try {
                setlocale(0, "");
                std::cout << "Введите количество вершин: ";
                size_t count;
                std::cin >> count;
                graph.generate_random_graph(count);
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 2:
        {
            try {
                setlocale(0, "");
                std::cout << "Вывод графа:\n" << std::endl;
                graph.print();
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 3:
        {
            try {
                setlocale(0, "");
                std::cout << "Введите начальную вершину: ";
                int start_from;
                std::cin >> start_from;
                std::cout << "Введите конечную вершину: ";
                int end_to;
                std::cin >> end_to;
                std::cout << "Кратчайший путь: " << std::endl;
                auto vector = graph.shortest_path(start_from, end_to);
                for (auto item : vector)
                    std::cout << item.from << "->" << item.to << " " << item.distance << std::endl;
                std::cout << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 4:
        {
            try {
                setlocale(0, "");
                std::cout << "Введите начальную вершину: ";
                int start_from;
                std::cin >> start_from;
                std::cout << "Обход в глубину: " << std::endl;
                auto vector = graph.walk(start_from);
                for (auto i : vector)
                    std::cout << i << "->";
                std::cout << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 5:
        {
            try {
                setlocale(0, "");
                std::cout << "Оптимальная вершина: " << find_optimal(graph) << std::endl;
            }
            catch (std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 6:
        {
            while (true) {
                text_menu2();
                int command2;
                std::cin >> command2;
                if (command2 == 0)
                    break;
                switch (command2) {
                case 1:
                {
                    while (true) {
                        setlocale(0, "");
                        std::cout << "[1] Добавить вершину\n"
                            << "[2] Добавить ребро\n"
                            << "[0] Назад\n"
                            << "--> ";
                        int command3;
                        std::cin >> command3;
                        if (command3 == 0) {
                            text_menu2();
                            break;
                        }

                        switch (command3) {
                        case 1:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите вершину: ";
                                int vertex;
                                std::cin >> vertex;
                                graph.add_vertex(vertex);
                                std::cout << "Вершина успешно добавлена!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите начальную вершину: ";
                                int start_vertex;
                                std::cin >> start_vertex;
                                std::cout << "Введите конечную вершину: ";
                                int end_vertex;
                                std::cin >> end_vertex;
                                std::cout << "Введите вес ребра: ";
                                double weight;
                                std::cin >> weight;
                                graph.add_edge(start_vertex, end_vertex, weight);
                                std::cout << "Ребро успешно добавлено!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                        {
                            setlocale(0, "");
                            std::cout << "Неверная команда!\n";
                            break;
                        }
                        }
                    }
                    break;
                }
                case 2:
                {
                    while (true) {
                        setlocale(0, "");
                        std::cout << "[1] Проверить вершину\n"
                            << "[2] Проверить ребро\n"
                            << "[0] Назад\n"
                            << "--> ";
                        int command3;
                        std::cin >> command3;
                        if (command3 == 0) {
                            text_menu2();
                            break;
                        }
                        switch (command3) {
                        case 1:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите вершину: ";
                                int vertex;
                                std::cin >> vertex;
                                if (graph.has_vertex(vertex))
                                    std::cout << "Вершина есть в графе!\n";
                                else
                                    std::cout << "Вершины нет в графе!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите начальную вершину: ";
                                int start_vertex;
                                std::cin >> start_vertex;
                                std::cout << "Введите конечную вершину: ";
                                int end_vertex;
                                std::cin >> end_vertex;
                                if (graph.has_edge(start_vertex, end_vertex))
                                    std::cout << "Ребро есть в графе!\n";
                                else
                                    std::cout << "Ребра нет в графе!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                        {
                            setlocale(0, "");
                            std::cout << "Неверная команда!\n";
                            break;
                        }
                        }
                    }
                }
                case 3:
                {
                    while (true) {
                        setlocale(0, "");
                        std::cout << "[1] Удалить вершину\n"
                            << "[2] Удалить ребро\n"
                            << "[0] Назад\n"
                            << "--> ";
                        int command3;
                        std::cin >> command3;
                        if (command3 == 0) {
                            text_menu2();
                            break;
                        }
                        switch (command3) {
                        case 1:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите вершину: ";
                                int vertex;
                                std::cin >> vertex;
                                graph.remove_vertex(vertex);
                                std::cout << "Вершина успешно удалена из графа!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 2:
                        {
                            try {
                                setlocale(0, "");
                                std::cout << "Введите начальную вершину: ";
                                int start_vertex;
                                std::cin >> start_vertex;
                                std::cout << "Введите конечную вершину: ";
                                int end_vertex;
                                std::cin >> end_vertex;
                                graph.remove_edge(start_vertex, end_vertex);
                                std::cout << "Ребро успешно удалено из графа!\n";
                            }
                            catch (std::invalid_argument& e) {
                                std::cout << e.what() << std::endl;
                            }
                            break;
                        }
                        case 0:
                        {
                            break;
                        }
                        default:
                        {
                            setlocale(0, "");
                            std::cout << "Неверная команда!\n";
                            break;
                        }
                        }
                    }
                    break;
                }
                case 4:
                {
                    try {
                        setlocale(0, "");
                        std::cout << "Введите вершину: ";
                        int vertex;
                        std::cin >> vertex;
                        std::cout << "Все ребра вершины (" << vertex << "): " << std::endl;
                        auto vector = graph.edges(vertex);
                        for (auto item : vector)
                            std::cout << item.from << "->" << item.to << " " << item.distance << std::endl;
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                }
                case 5:
                {
                    try {
                        setlocale(0, "");
                        std::cout << "Порядок графа: " << graph.order() << std::endl;
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                }
                case 6:
                {
                    try {
                        setlocale(0, "");
                        std::cout << "Макс.Степень вершины графа: " << graph.degree() << std::endl;
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                }
                case 0:
                {
                    break;
                }
                default:
                {
                    setlocale(0, "");
                    std::cout << "Неверная команда!\n";
                    break;
                }
                }
            }
            break;
        }
        case 7:
        {
            while (true) {
                setlocale(0, "");
                std::cout << "[1] Граф с вершинами 1, 2, 3, 4\n"
                    << "[2] Граф с вершинами 1, 2, 3, 4, 5\n"
                    << "[0] Назад\n"
                    << "--> ";
                int command3;
                std::cin >> command3;
                if (command3 == 0) {
                    text_menu2();
                    break;
                }
                switch (command3) {
                case 1:
                {
                    try {
                        // опт.вершина - 1
                        graph.add_vertex(1);
                        graph.add_vertex(2);
                        graph.add_vertex(3);
                        graph.add_vertex(4);
                        graph.add_edge(1, 2, 1);
                        graph.add_edge(2, 3, 3);
                        graph.add_edge(1, 3, 5);
                        graph.add_edge(3, 1, 2);
                        graph.add_edge(1, 4, 12);
                        graph.add_edge(4, 1, 10);
                        std::cout << "Тестовый граф с вершинами 1, 2, 3, 4, 5 - успешно загружен!\n";
                    }
                    catch (std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                }
                case 2:
                {
                    try {
                        // опт.вершина - 2
                        graph.add_vertex(1);
                        graph.add_vertex(2);
                        graph.add_vertex(3);
                        graph.add_vertex(4);
                        graph.add_vertex(5);
                        graph.add_edge(1, 2, 10);
                        graph.add_edge(1, 3, 5);
                        graph.add_edge(3, 2, 3);
                        graph.add_edge(3, 4, 2);
                        graph.add_edge(2, 3, 2);
                        graph.add_edge(4, 1, 7);
                        graph.add_edge(2, 5, 1);
                        graph.add_edge(4, 5, 4);
                        graph.add_edge(5, 4, 6);
                    }
                    catch (std::exception& e) {
                        std::cout << e.what() << std::endl;
                    }
                    break;
                }
                case 0:
                {
                    break;
                }
                default:
                {
                    std::cout << "Неверная команда!\n";
                    break;
                }
                }
            }
            break;
        }
        case 0:
        {
            setlocale(0, "");
            std::cout << "Выход из программы!\n";
            return 0;
        }
        default:
        {
            setlocale(0, "");
            std::cout << "Неверная команда!\n";
            break;
        }
        }

    }
    return 0;
}