#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>
#include <fstream>


#include <memory>



//Берем стопку изображений из файла.nii, узнаем количество изображений в стопке Z, узнаем размеры изображений X, Y;
//X, Y, Z - координаты
//Вершина графа - геометрический центр сегментированного белого пятна на изображении
//Также в вершине графа хранится координаты геометрического центра пятна, площадь пятна, соответствующего этой вершине.



//Подсчет площади (в пикселях) всех пятен на изображении
//int AllSpotsSquare(cv::Mat sliceImg) {
//    int square = 0;
//    for (int i = 0; i < sliceImg.rows; i++) {
//        for (int j = 0; j < sliceImg.cols; j++) {
//            if ((int) sliceImg.at<uchar>(i, j) != 0) {
//                square += 1;
//            }
//        }
//    }
//    return square;
//}

//Вектор с контурами пятен
std::vector<std::vector<cv::Point>> ContoursVector(cv::Mat sliceImg) {
    cv::Mat img;
    cv::Mat gray;
    cv::Mat binary;

    sliceImg.copyTo(img);

    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, binary, 150, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    return contours;
}

//Площадь контура по формуле Гаусса
double ContourSquare(std::vector<cv::Point> contour) {
    double square = 0;
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 0; i < contour.size() - 1; i++) {
        sum1 += contour[i].y * contour[i + 1].x;
    }

    for (int i = 1; i < contour.size(); i++) {
        sum2 += contour[i].y * contour[i - 1].x;
    }

    square = sum1 + contour[contour.size() - 1].y * contour[0].x - sum2 - contour[0].y * contour[contour.size() - 1].x;
    square = square * 0.5;
    square += (double) contour.size() / 2;
    return square;
}

//Общая площадь всех контуров на изображении
int AllSpotsSquare(cv::Mat sliceImg) {
    double square = 0;
    std::vector<std::vector<cv::Point>> contours = ContoursVector(sliceImg);

    for (int i = 0; i < contours.size(); i++) {
        std::vector<cv::Point> contour = contours[i];
        square += ContourSquare(contour);
    }

    return square;
}

//Вектор с площадями пятен
std::vector<double> GetSquaresVector(cv::Mat sliceImg){
    std::vector<double> squares;
    std::vector<std::vector<cv::Point>> contours;

    for (int i = 0; i < contours.size(); i++){
        squares.push_back(ContourSquare(contours[i]));
    }

    return squares;
}

//Вывод координат отдельных контуров на изображении
void ShowContoursCoords(cv::Mat sliceImg) {
    std::vector<std::vector<cv::Point>> contours = ContoursVector(sliceImg);
    for (int i = 0; i < contours.size(); i++) {
        std::cout << "Spot #" << i + 1 << '\n';
        for (int j = 0; j < contours[i].size(); j++) {
            std::cout << contours[i][j].y << ' ' << contours[i][j].x << '\n';
        }
    }
}

//Координаты центра контура
std::vector<double> GetCentreCoords(std::vector<cv::Point> contour){
    double sumx = 0;
    double sumy = 0;
    std::vector<double> coords;

    for(int i = 0; i < contour.size(); i++){
        sumx += contour[i].y;
        sumy += contour[i].x;
    }

    coords.push_back(round(sumx / contour.size()));
    coords.push_back(round(sumy / contour.size()));

    return coords;
}

//Вектор с координатами центров всех пятен
std::vector<std::vector<double>> GetCentresVector(cv::Mat sliceImg){
    std::vector<std::vector<cv::Point>> contours;
    contours = ContoursVector(sliceImg);

    std::vector<std::vector<double>> centres;
    std::vector<double> coords;

    for (int i = 0; i < contours.size(); i++){
        coords = GetCentreCoords(contours[i]);
        centres.push_back(coords);
    }

    return centres;
}

//Визуализация вектора с центрами пятен
void ShowCentresVector(std::vector<std::vector<double>> coords){
    for(int i = 0; i < coords.size(); i++){
        std::cout << coords[i][0] << ' ' << coords[i][1] << '\n';
    }
}

//Вектор ребер отдельного контура
std::vector<std::vector<int>> EdgesVector(std::vector<cv::Point> contour){
    std::vector<std::vector<int>> edges;
    for (int  i = 0; i < contour.size() - 1; i++){
        std::vector<int> coords;
        coords.push_back(contour[i].y);
        coords.push_back(contour[i].x);
        coords.push_back(contour[i + 1].y);
        coords.push_back(contour[i + 1].x);
        edges.push_back(coords);
    }
    std::vector<int> last_coords;
    last_coords.push_back(contour[contour.size() - 1].y);
    last_coords.push_back(contour[contour.size() - 1].x);
    last_coords.push_back(contour[0].y);
    last_coords.push_back(contour[0].x);
    edges.push_back(last_coords);

    return edges;
}

//Нахождение коэффициента k
double GetK(int x1, int y1, int x2, int y2){
    double k = 0;
    k = ((double) y1 - (double) y2) / ((double) x1 - (double) x2);

    return k;
}

//Нахождение коэффициента b
double GetB(int x1, int y1, double k){
    double b = (double) y1 - k * ((double) x1);

    return b;
}

//Нахождение точки пересечения
std::vector<double> GetIntersectionPoint(double k1, double k2, double b1, double b2){
    std::vector<double> point;
    double x = 0;
    double y = 0;

    x = (b2 - b1) / (k1 - k2);
    y = k1 * x + b1;
    point.push_back(x);
    point.push_back(y);

    return point;

}

//Проверка пересечения двух отрезков РАБОТАЕТ
bool SegmentIntersection(std::vector<int> coords1, std::vector<int> coords2){
    int flag1 = 0;
    int flag2 = 0;

    int x11 = coords1[0];
    int y11 = coords1[1];
    int x12 = coords1[2];
    int y12 = coords1[3];
    double k1 = GetK(x11, y11, x12, y12);
    //std::cout << "k1=" << k1 << '\n';
    double b1 = GetB(x11, y11, k1);
    //std::cout << "b1=" << b1 << '\n';

    int x21 = coords2[0];
    int y21 = coords2[1];
    int x22 = coords2[2];
    int y22 = coords2[3];
    double k2 = GetK(x21, y21, x22, y22);
    //std::cout << "k2=" << k2 << '\n';
    double b2 = GetB(x21, y21, k2);
    //std::cout << "b2=" << b2 << '\n';

    std::vector<double> i_point;
    i_point = GetIntersectionPoint(k1, k2, b1, b2);
//    std::cout << "x=" << i_point[0] << '\n';
//    std::cout << "y=" << i_point[1] << '\n';
//
//    std::cout << "x11=" << std::min(x11, x12) << '\n';
//    std::cout << "x12=" << std::max(x11, x12) << '\n';
//    std::cout << "x21=" << std::min(x21, x22) << '\n';
//    std::cout << "x22=" << std::max(x21, x22) << '\n';
//
//    std::cout << "y11=" << std::min(y11, y12) << '\n';
//    std::cout << "y12=" << std::max(y11, y12) << '\n';
//    std::cout << "y21=" << std::min(y21, y22) << '\n';
//    std::cout << "y22=" << std::max(y21, y22) << '\n';

    if (
            (double) std::min(x11, x12) <= i_point[0] && i_point[0] <= (double) std::max(x11, x12) &&
            (double) std::min(x21, x22) <= i_point[0] && i_point[0] <= (double) std::max(x21, x22)){
        flag1 = 1;
    }

    if (
            (double) std::min(y11, y12) <= i_point[1] && i_point[1] <= (double) std::max(y11, y12) &&
            (double) std::min(y21, y22) <= i_point[1] && i_point[1] <= (double) std::max(y21, y22)){
        flag2 = 1;
    }

    if(flag1 && flag2){
        return true;
    }
    else{
        return false;
    }
}

//Проверка пересечения двух контуров
bool ContoursIntersection(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2){
    std::vector<std::vector<int>> edges1;
    std::vector<std::vector<int>> edges2;

    edges1 = EdgesVector(contour1);
    edges2 = EdgesVector(contour2);

    int flag = 0;

    for (int i = 0; i < contour1.size(); i++){
        for (int j = 0; j < contour2.size(); j++){
            if(SegmentIntersection(edges1[i], edges2[j])){
                flag = 1;
                break;
            };
        }
        if (flag){
            break;
        }
    }

    if(flag){
        return true;
    }
    else{
        return false;
    }
}

//Проверка того, что точка лежит внутри контура
bool PointInsideContour(cv::Point point, std::vector<cv::Point> contour){
    int flag1 = 0; //x left
    int flag2 = 0; //x right
    int flag3 = 0; //y up
    int flag4 = 0; //y down

    for(int i = 0; i < contour.size(); i++){
        if(contour[i].y <= point.y){
            flag1 = 1;
        }
        if(contour[i].y >= point.y){
            flag2 = 1;
        }
        if(contour[i].x >= point.x){
            flag3 = 1;
        }
        if(contour[i].x <= point.x){
            flag4 = 1;
        }
    }

    if(flag1 && flag2 && flag3 && flag4){
        return true;
    }
    else{
        return false;
    }
}

//Нужна проверка того, что один контур лежит внутри другого контура
bool ContoursInside(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2){
    std::vector<double> coords1 = GetCentreCoords(contour1);
    cv::Point centre1 = cv::Point((int) coords1[1], (int) coords1[0]);

    std::vector<double> coords2 = GetCentreCoords(contour2);
    cv::Point centre2 = cv::Point((int) coords2[1], (int) coords2[0]);

    if(PointInsideContour(centre1, contour2) || PointInsideContour(centre2, contour1)){
        return true;
    }
    else{
        return false;
    }
}

//Класс вершины графа
class Vertice{
public:
    int number = -1;
    std::vector<double> centre = {0, 0};
    double square = 0;
    std::vector<cv::Point> contour;
    int component = -1;

    bool operator==(const Vertice& rhs) const;
    bool operator!=(const Vertice& rhs) const;
    bool operator>=(const Vertice& rhs) const;
    bool operator<=(const Vertice& rhs) const;
    bool operator>(const Vertice& rhs) const;
    bool operator<(const Vertice& rhs) const;
};

bool Vertice::operator!=(const Vertice &rhs) const{
    return (number != rhs.number && (square != rhs.square || (centre[0] != rhs.centre[0] && centre[1] != rhs.centre[1])));
}
bool Vertice::operator==(const Vertice &rhs) const{
    return (number == rhs.number || square == rhs.square && (centre[0] == rhs.centre[0] && centre[1] == rhs.centre[1]));
}
bool Vertice::operator>=(const Vertice &rhs) const{
    return (number >= rhs.number || square >= rhs.square || (centre[0] >= rhs.centre[0] && centre[1] >= rhs.centre[1]));
}
bool Vertice::operator<=(const Vertice &rhs) const{
    return (number <= rhs.number || square <= rhs.square || (centre[0] <= rhs.centre[0] && centre[1] <= rhs.centre[1]));
}
bool Vertice::operator>(const Vertice &rhs) const{
    return (number > rhs.number || square > rhs.square || (centre[0] > rhs.centre[0] && centre[1] > rhs.centre[1]));
}
bool Vertice::operator<(const Vertice &rhs) const{
    return (number < rhs.number || square < rhs.square || (centre[0] < rhs.centre[0] && centre[1] < rhs.centre[1]));
}



//Граф с вершинами, которые соответствуют пятнам
//Граф хранится в виде списка ребер в формате (Вершина, Вершина)
std::vector<std::pair<Vertice, Vertice>> GetGraph(std::vector<cv::Mat> slices){
    std::vector<std::pair<Vertice, Vertice>> graph;
    std::set<Vertice> vertices;
    int num = 0;

    for (int i = 0; i < slices.size() - 1; i++){
        std::vector<std::vector<cv::Point>> contours_vector1 = ContoursVector(slices[i]);
        std::vector<std::vector<cv::Point>> contours_vector2 = ContoursVector(slices[i + 1]);
        for (int j = 0; j < contours_vector1.size(); j++){
            Vertice v1 = Vertice();
            std::vector<cv::Point> contour1 = contours_vector1[j];
            v1.centre = GetCentreCoords(contour1);
            v1.square = ContourSquare(contour1);
            v1.contour = contour1;

            for(int k = 0; k < contours_vector2.size(); k++){
                std::vector<cv::Point> contour2 = contours_vector2[k];
                Vertice v2 = Vertice();
                v2.centre = GetCentreCoords(contour2);
                v2.square = ContourSquare(contour2);
                v2.contour = contour2;

                if (ContoursIntersection(contour1, contour2) || ContoursInside(contour1, contour2)){
                    std::pair<Vertice, Vertice> pair = std::make_pair(v1, v2);
                    //std::cout << v1.square << ' ' << v2.square << '\n';
                    graph.push_back(pair);
                }
            }
        }
    }
//Добавляю вершинам номера
    graph[0].first.number = num;
    num += 1;
    graph[0].second.number = num;
    num += 1;
    vertices.insert(graph[0].first);
    vertices.insert(graph[0].second);

    for(int i = 1; i < graph.size(); i++){
        Vertice v1 = graph[i].first;
        Vertice v2 = graph[i].second;

        int flag = 1;
        for(Vertice item: vertices){
            if (item == graph[i].first){
                graph[i].first.number = item.number;
                flag = 0;
            }
        }
        if (flag){
            graph[i].first.number = num;
            num += 1;
            vertices.insert(graph[i].first);
        }

        flag = 1;
        for(Vertice item: vertices){
            if (item == graph[i].second){
                graph[i].second.number = item.number;
                flag = 0;
            }
        }
        if (flag){
            graph[i].second.number = num;
            num += 1;
            vertices.insert(graph[i].second);
        }
    }

    return graph;
}

//Строю списки смежности для графа
std::vector<std::vector<int>> AdList(std::vector<std::pair<Vertice, Vertice>> graph){
    std::set<int> numbers;
    for (int i = 0; i < graph.size(); i++){
        numbers.insert(graph[i].first.number);
        numbers.insert(graph[i].second.number);
    }

    std::vector<std::vector<int>> matrix(numbers.size());

    for(int i = 0; i < matrix.size(); i++){
        std::vector<int> line;
        for (int j = 0; j < graph.size(); j++) {
            if (graph[j].first.number == i) {
                line.push_back(graph[j].second.number);
            }
        }
        matrix[i] = line;
    }
    return matrix;
}

void ShowAdList(std::vector<std::vector<int>> matrix){
    for (int i = 0; i < matrix.size(); i++) {
        std::cout << i << ':' << ' ';
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix.at(i).at(j) << ' ';
        }
        std::cout << '\n';
    }
}

void Dfs(std::vector<std::vector<int>> &matrix, int v, std::vector<int> &visited, std::vector<int> &component){
    visited[v] = 1;
    component.push_back(v);

    for (int to : matrix[v])
        if (!visited[to])
            Dfs(matrix, to, visited, component);
}

//Вектор с рапределением графа на компоненты связности
std::vector<std::vector<int>> FindComps(std::vector<std::vector<int>> &matrix, int v, std::vector<int> &visited, std::vector<int> &component)
{
    std::vector<std::vector<int>> comp;
    for (int i = 0; i < v; ++i)
        visited[i] = 0;
    for (int i = 0; i < v; ++i)
        if (!visited[i])
        {
            std::vector<int> line;
            component.clear();
            Dfs(matrix, i, visited, component);

            sort(component.begin(), component.end());
            //std::cout << "Component:" << std::endl;
            for (int i = 0; i < component.size(); i++) //выводим все вершины компоненты
            {
                for (int j = 0; j < matrix[component[i]].size(); j++) { //выводим все смежные вершины и у текущей
                    line.push_back(matrix[component[i]][j]);
                    //std::cout << matrix[component[i]][j] << " ";
                }
                //std::cout << std::endl;
            }
            line.push_back(i);
            sort(line.begin(), line.end());
            comp.push_back(line);
        }
    return comp;
}

//std::vector<std::vector<int>> GetComponents(std::vector<std::vector<int>> matrix){
//    int v = matrix.size();
//    std::vector<int> visited;
//    std::vector<int> component;
//    std::vector<std::vector<int>> comp;
//
//    comp = FindComps(matrix, v, visited, component);
//    return comp;
//}

//Присвоение вершинам графа информации о том, к какой компоненте связности они относятся
void ComponentsOfVertices(std::vector<std::pair<Vertice, Vertice>> &graph, std::vector<std::vector<int>> &comp){
//    std::cout << "Work!" << '\n';
//    for (int i = 0; i < graph.size(); i++){
//        std::cout <<'(' << graph[i].first.centre[0] << ',' << graph[i].first.centre[1] << ')'  << graph[i].first.number << ' '
//                  << '(' << graph[i].second.centre[0] << ',' << graph[i].second.centre[1] << ')' << graph[i].second.number << '\n';
//    }

    //std::cout << "Please" << '\n';

    for(int i = 0; i < comp.size(); i++){
        for(int j = 0; j < comp[i].size(); j++){
            for (int k = 0; k < graph.size(); k ++){
//                std::cout << graph[k].first.number << ' ' << comp[i][j] << '\n';
//                std::cout << graph[k].second.number << ' ' << comp[i][j] << '\n';
                if(graph[k].first.number == comp[i][j]){
                    graph[k].first.component = i;
                }
                if (graph[k].second.number == comp[i][j]){
                    graph[k].second.component = i;
                }
            }
        }
    }
}

//Число компонент в графе
int ComponentsNumber(std::vector<std::pair<Vertice, Vertice>> graph){
    std::set<int> components;
    for (int i = 0; i < graph.size(); i++){
        components.insert(graph[i].first.component);
        components.insert(graph[i].second.component);
    }

    return components.size();
}

//Множество вершин графа
std::set<Vertice> Vertices(std::vector<std::pair<Vertice, Vertice>> graph){
    std::set<Vertice> vertices;
    for (int i = 0; i < graph.size(); i++){
        vertices.insert(graph[i].first);
        vertices.insert(graph[i].second);
    }
    return vertices;
}

//Количество вершин графа
int VerticesNumber(std::vector<std::pair<Vertice, Vertice>> graph){
    std::set<Vertice> vertices;
    vertices = Vertices(graph);
    return vertices.size();
}

//Подсчет объемов компонент связности
std::vector<double> ComponentsVolumes(std::vector<std::pair<Vertice, Vertice>> graph){
    int size = ComponentsNumber(graph);
    std::vector<double> volumes(size);

    std::set<Vertice> vertices = Vertices(graph);
    for (int i = 0; i < size; i++){
        double volume = 0;
        for(Vertice item: vertices){
            if(item.component == i){
                volume += item.square;
            }
        }
        volumes[i] = volume;
    }
    return volumes;
}

//Вывод вектора с объемами по компонентам
void ShowVolumes(std::vector<double> volumes){
    std::cout << "Volumes\n";
    for (int i = 0; i < volumes.size(); i++){
        std::cout << "Component " << i << ": " << volumes[i] << '\n';
    }
}

//Вектор длин компонент связности
std::vector<int> ComponentsLengths(std::vector<std::pair<Vertice, Vertice>> graph){
    int size = ComponentsNumber(graph);
    std::vector<int> lengths(size);
    std::set<Vertice> vertices = Vertices(graph);

    for (int i = 0; i < size; i++){
        int length = 0;
        for(int j = 0; j < graph.size(); j++){
            if(graph[j].second.component == i){
                length += 1;
            }
        }
        lengths[i] = length;
    }
    return lengths;
}

//Вывод вектора с длинами компонент связности
void ShowLengths(std::vector<int> lengths){
    std::cout << "Lengths\n";
    for (int i = 0; i < lengths.size(); i++){
        std::cout << "Component " << i << ": " << lengths[i] << '\n';
    }
}

//Создание матрицы смежности
std::vector<std::vector<int>> AdMatrix(std::vector<std::pair<Vertice, Vertice>> graph){
    int size = VerticesNumber(graph);
    std::vector<std::vector<int>> matrix(size);

    for (int i = 0; i < size; i++){
        std::vector<int> line(size);
        for(int j = 0; j < line.size(); j++){
            line[j] = 0;
        }
        matrix[i] = line;
    }

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < graph.size(); k++){
                int n1 = graph[k].first.number;
                int n2 = graph[k].second.number;
                matrix[n1][n2] = 1;
            }
        }
    }
    return matrix;
}

//Вывод матрицы смежности графа
void ShowAdMatrix(std::vector<std::vector<int>> matrix){
    std::cout << "AdMatrix\n";
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

//Подсчет количества листьев в компонентах
std::vector<int> ComponentsLeaves(std::vector<std::pair<Vertice, Vertice>> graph){
    int size = ComponentsNumber(graph);
    std::vector<int> leaves(size);
    for (int i = 0; i < leaves.size(); i ++){
        leaves[i] = 0;
    }

    std::vector<std::vector<int>> matrix = AdMatrix(graph);
    std::set<Vertice> vertices = Vertices(graph);

    for(int i = 0; i < matrix.size(); i++){
        int flag = 1;
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[i][j] == 1){
                flag = 0;
            }
        }
        int comp = 0;
        for (Vertice item: vertices){
            if (i == item.number){
                comp = item.component;
            }
        }
        if (flag){
            leaves[comp] += 1;
        }
    }

    return leaves;
}

//Вывод вектора с количеством листьев в компонентах
void ShowLeaves(std::vector<int> leaves){
    std::cout << "Leaves\n";
    for (int i = 0; i < leaves.size(); i++){
        std::cout << "Component " << i << ": " << leaves[i] << '\n';
    }
}















//КОД МАКСА
namespace niipars {
    template<typename dtype>
    std::vector<cv::Mat> read_slices(std::ifstream& is, const int& num_slices, const int& w, const int& h) {
        const int buffer_size = num_slices * w * h;

        std::unique_ptr<dtype[]> data(new dtype[buffer_size]);
        is.read(reinterpret_cast <char*>(data.get()), sizeof(dtype) * buffer_size);

        std::vector<cv::Mat> slices(num_slices);

        for (int i = 0; i < num_slices; ++i) {
            slices[i] = cv::Mat(w, h, CV_32SC1);
            int* img_data = (int*)(slices[i].data);

            for (int j = 0; j < w; ++j)
                for (int k = 0; k < h; ++k) {
                    const int idx1 = j * h + k;
                    const int idx2 = (k * w + j) * num_slices + i;
                    img_data[idx1] = data[idx2];
                }
        }

        return slices;
    }

    std::vector<cv::Mat> read_nifti(const std::string& filename) {
        int header_size;
        short int num_slices;
        short int w, h;
        short int dtype;

        std::ifstream is(filename, std::ios::binary | std::ios::in);

        if (!is) {
            std::cerr << "invalid filename" << std::endl;
            std::exit(1);
        }

        is.read(reinterpret_cast <char*>(&header_size), sizeof(int));
        is.seekg(0);
        is.seekg(42);

        is.read(reinterpret_cast <char*>(&num_slices), sizeof(short int));
        is.read(reinterpret_cast <char*>(&w), sizeof(short int));
        is.read(reinterpret_cast <char*>(&h), sizeof(short int));

        is.seekg(0);
        is.seekg(70);
        is.read(reinterpret_cast <char*>(&dtype), sizeof(short int));

        is.seekg(0);
        is.seekg(header_size);

        std::vector<cv::Mat> slices(num_slices);

        switch (dtype) {
            case 4: // short int
                slices = read_slices<short>(is, num_slices, w, h);
                break;
            case 16: // float
                slices = read_slices<float>(is, num_slices, w, h);
                break;
            case 64: // long long
                slices = read_slices<long long>(is, num_slices, w, h);
                break;
            case 512:
                slices = read_slices<int16_t>(is, num_slices, w, h);
                break;
            default: {
                std::cerr << "Parser type not understood!" << std::endl
                          << "Please see the documentation at https://brainder.org/2012/09/23/the-nifti-file-format/ "
                          << "and add a new item in the switch format according to the found value (" << dtype << ")"
                          << std::endl;
            }
                break;
                // add more cases here according to your needs
        }

        is.close();

        return slices;
    }

    void convert_to_show(cv::Mat& slice) {
        cv::normalize(slice, slice, 0, 255, cv::NORM_MINMAX);
        slice.convertTo(slice, CV_8UC1);
        return;
    }

    std::vector<cv::Mat> convert_stack_to_show(const std::vector<cv::Mat>& slices) {
        std::vector<cv::Mat> convertedSlices;
        for (auto slice : slices) {
            convert_to_show(slice);
            convertedSlices.push_back(slice);

        }
        return convertedSlices;
    }

    std::vector<cv::Mat> switch_view_nifti(std::vector<cv::Mat> slices) {

        auto slices_top = slices;

        for (int k = 0; k < slices.size(); k++) {
            auto s = slices[0];
            int* ouput = (int*)(s.data);
            for (int j = 0; j < s.rows; j++) {
                for (int i = 0; i < s.cols; i++) {
                    auto img = slices[i];
                    int* input = (int*)(img.data);
                    ouput[s.cols * j + i] = input[img.cols * k + j];
                    ouput[s.cols * j + i + 1] = input[img.cols * k + j + 1];
                    ouput[s.cols * j + i + 2] = input[img.cols * k + j + 2];
                }
            }
            convert_to_show(s);
            s.copyTo(slices_top[k]);
        }
        return slices_top;
    }

    std::vector<int16_t> get_p(cv::Mat img, int i, int j) {
        std::vector<int16_t> RGB(3);
        int16_t* input = (int16_t*)(img.data);
        RGB[0] = input[img.cols * j + i];
        RGB[1] = input[img.cols * j + i + 1];
        RGB[2] = input[img.cols * j + i + 2];
        return RGB;
    }

    std::vector<cv::Mat> top_view_nifti(std::vector<cv::Mat> slices) {

        auto slices_top = slices;


        for (int k = 0; k < slices.size(); k++) {
            auto s = slices[0];
            int* ouput = (int*)(s.data);
            for (int j = 0; j < s.rows; j++) {
                for (int i = 0; i < s.cols; i++) {
                    auto img = slices[i];
                    int* input = (int*)(img.data);
                    ouput[s.cols * j + i] = input[img.cols * k + j];
                    ouput[s.cols * j + i + 1] = input[img.cols * k + j + 1];
                    ouput[s.cols * j + i + 2] = input[img.cols * k + j + 2];
                }
            }
            cv::normalize(s, s, 0, 255, cv::NORM_MINMAX);
            s.convertTo(s, CV_8UC1);
            s.copyTo(slices_top[k]);
        }
        return slices_top;
    }

}