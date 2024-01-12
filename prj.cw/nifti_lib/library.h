#include<iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>
#include <fstream>
#include "library.h"


#include <memory>

//Вектор с контурами пятен
std::vector<std::vector<cv::Point>> ContoursVector(cv::Mat sliceImg);
//Площадь контура по формуле Гаусса
double ContourSquare(std::vector<cv::Point> contour);
//Общая площадь всех контуров на изображении
int AllSpotsSquare(cv::Mat sliceImg);
//Вектор с площадями пятен
std::vector<double> GetSquaresVector(cv::Mat sliceImg);
//Вывод координат отдельных контуров на изображении
void ShowContoursCoords(cv::Mat sliceImg);
//Координаты центра контура
std::vector<double> GetCentreCoords(std::vector<cv::Point> contour);
//Вектор с координатами центров всех пятен
std::vector<std::vector<double>> GetCentresVector(cv::Mat sliceImg);
//Визуализация вектора с центрами пятен
void ShowCentresVector(std::vector<std::vector<double>> coords);
//Вектор ребер отдельного контура
std::vector<std::vector<int>> EdgesVector(std::vector<cv::Point> contour);
//Нахождение коэффициента k
double GetK(int x1, int y1, int x2, int y2);
//Нахождение коэффициента b
double GetB(int x1, int y1, double k);
//Нахождение точки пересечения
std::vector<double> GetIntersectionPoint(double k1, double k2, double b1, double b2);
//Проверка пересечения двух отрезков РАБОТАЕТ
bool SegmentIntersection(std::vector<int> coords1, std::vector<int> coords2);
//Проверка пересечения двух контуров
bool ContoursIntersection(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2);
//Проверка того, что точка лежит внутри контура
bool PointInsideContour(cv::Point point, std::vector<cv::Point> contour);
//Нужна проверка того, что один контур лежит внутри другого контура
bool ContoursInside(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2);
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

bool Vertice::operator!=(const Vertice &rhs) const;
bool Vertice::operator==(const Vertice &rhs) const;
bool Vertice::operator>=(const Vertice &rhs) const;
bool Vertice::operator<=(const Vertice &rhs) const;
bool Vertice::operator>(const Vertice &rhs) const;
bool Vertice::operator<(const Vertice &rhs) const;



//Граф с вершинами, которые соответствуют пятнам
//Граф хранится в виде списка ребер в формате (Вершина, Вершина)
std::vector<std::pair<Vertice, Vertice>> GetGraph(std::vector<cv::Mat> slices);

//Строю списки смежности для графа
std::vector<std::vector<int>> AdList(std::vector<std::pair<Vertice, Vertice>> graph);

void ShowAdList(std::vector<std::vector<int>> matrix);
void Dfs(std::vector<std::vector<int>> &matrix, int v, std::vector<int> &visited, std::vector<int> &component);
//Вектор с рапределением графа на компоненты связности
std::vector<std::vector<int>> FindComps(std::vector<std::vector<int>> &matrix, int v, std::vector<int> &visited, std::vector<int> &component);

//Присвоение вершинам графа информации о том, к какой компоненте связности они относятся
void ComponentsOfVertices(std::vector<std::pair<Vertice, Vertice>> &graph, std::vector<std::vector<int>> &comp);

//Число компонент в графе
int ComponentsNumber(std::vector<std::pair<Vertice, Vertice>> graph);

//Множество вершин графа
std::set<Vertice> Vertices(std::vector<std::pair<Vertice, Vertice>> graph);

//Количество вершин графа
int VerticesNumber(std::vector<std::pair<Vertice, Vertice>> graph);

//Подсчет объемов компонент связности
std::vector<double> ComponentsVolumes(std::vector<std::pair<Vertice, Vertice>> graph);

//Вывод вектора с объемами по компонентам
void ShowVolumes(std::vector<double> volumes);

//Вектор длин компонент связности
std::vector<int> ComponentsLengths(std::vector<std::pair<Vertice, Vertice>> graph);

//Вывод вектора с длинами компонент связности
void ShowLengths(std::vector<int> lengths);
//Создание матрицы смежности
std::vector<std::vector<int>> AdMatrix(std::vector<std::pair<Vertice, Vertice>> graph);

//Вывод матрицы смежности графа
void ShowAdMatrix(std::vector<std::vector<int>> matrix);

//Подсчет количества листьев в компонентах
std::vector<int> ComponentsLeaves(std::vector<std::pair<Vertice, Vertice>> graph);

//Вывод вектора с количеством листьев в компонентах
void ShowLeaves(std::vector<int> leaves);
