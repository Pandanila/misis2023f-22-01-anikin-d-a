#include "nifti_lib/library.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main() {
    //int square = 0;
    //std::vector<cv::Mat> slices = niipars::read_nifti("C:/cv/test/test.nii");
    //std::vector<cv::Mat> slices_top = niipars::top_view_nifti(slices);
    //std::vector<cv::Mat> suka = niipars::switch_view_nifti(slices);
    //cv::Mat slice = slices_top[245];
    //cv::Mat img;
    //slice.copyTo(img);

    //std::cout << img.type();

    cv::Mat img1 = cv::imread("C:/Users/danan/Downloads/contour1.jpg");
    cv::Mat img2 = cv::imread("C:/Users/danan/Downloads/contour2.jpg");
    cv::Mat img3 = cv::imread("C:/Users/danan/Downloads/contour3.jpg");
    cv::Mat img4 = cv::imread("C:/Users/danan/Downloads/contour4.jpg");
    cv::Mat img5 = cv::imread("C:/Users/danan/Downloads/contour5.jpg");
    cv::Mat img6 = cv::imread("C:/Users/danan/Downloads/contour6.jpg");
    cv::Mat img7 = cv::imread("C:/Users/danan/Downloads/contour7.jpg");
    cv::Mat img8 = cv::imread("C:/Users/danan/Downloads/contour8.jpg");
    cv::Mat img9 = cv::imread("C:/Users/danan/Downloads/contour9.jpg");


    std::vector<cv::Mat> slices;
    slices.push_back(img1);
    slices.push_back(img2);
    slices.push_back(img3);
    slices.push_back(img4);
    slices.push_back(img5);
    slices.push_back(img6);
    slices.push_back(img7);
    slices.push_back(img8);
    slices.push_back(img9);

    std::vector<std::pair<Vertice, Vertice>> graph = GetGraph(slices);

//    for (int i = 0; i < graph.size(); i++){
//        std::cout <<'(' << graph[i].first.centre[0] << ',' << graph[i].first.centre[1] << ')'  << graph[i].first.number << ' '
//        << '(' << graph[i].second.centre[0] << ',' << graph[i].second.centre[1] << ')' << graph[i].second.number << '\n';
//    }
    std::vector<std::vector<int>> alist = AdList(graph);
    std::vector<int> visited(alist.size());
    std::vector<int> component;
    std::vector<std::vector<int>> comp = FindComps(alist, alist.size(), visited, component);
//    std::cout << "ura" << '\n';
//    for(int i = 0; i < comp.size(); i++){
//        std::cout << i << ":\n";
//        for(int j = 0; j < comp[i].size(); j++){
//            std::cout << comp[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }
    ComponentsOfVertices(graph, comp);
    std::cout << "Attention" << '\n';
//    for (int i = 0; i < graph.size(); i++){
//        std::cout <<'(' << graph[i].first.centre[0] << ',' << graph[i].first.centre[1] << ')'  << graph[i].first.number << ' ' << graph[i].first.component << ' '
//                  << '(' << graph[i].second.centre[0] << ',' << graph[i].second.centre[1] << ')' << graph[i].second.number << ' ' << graph[i].second.component << '\n';
//    }
    std::cout << "Graph\n";
    for (int i = 0; i < graph.size(); i++){
        std::cout <<'(' << graph[i].first.number << ' ' << graph[i].second.number << ')' << '\n';
    }


    std::vector<double> volumes = ComponentsVolumes(graph);
    std::vector<int> lengths = ComponentsLengths(graph);
    std::vector<std::vector<int>> matrix = AdMatrix(graph);
    std::vector<int> leaves = ComponentsLeaves(graph);
    ShowAdMatrix(matrix);
    ShowVolumes(volumes);
    ShowLengths(lengths);
    ShowLeaves(leaves);
//    for(int i = 0; i < comp.size(); i++){
//        std::cout << i << ':';
//        for(int j = 0; j < comp[i].size(); j++){
//            std::cout << comp[i][j] << ' ';
//        }
//        std::cout << '\n';
//    }




    //ShowContoursCoords(img);

//    std::vector<int> coords1 = {10, 4, 2, 2};
//    std::vector<int> coords2 = {8, 2, 7, 5};
//
//    std::cout << SegmentIntersection(coords1, coords2);
//    double square1 = 0;
//    double square2 = 0;

//    for (int i = 0; i < img.rows; i++) {
//        for (int j = 0; j < img.cols; j++) {
//            if ((int) img.at<cv::Vec3b>(i, j)[0] > 150 && (int) img.at<cv::Vec3b>(i, j)[1] > 150 && (int) img.at<cv::Vec3b>(i, j)[2] > 150) {
//                square1 += 1;
//            }
//        }
//    }

//    square2 = AllSpotsSquare(img);
//
//
//    std::cout << square1 << '\n';
//    std::cout << square2 << '\n';

    //cv::Mat gray;
    //cv::Mat binary;

    ////img.convertTo(img, CV_8UC3);
    //cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    //cv::threshold(gray, binary, 150, 255, cv::THRESH_BINARY);
    //std::vector<std::vector<cv::Point>> contours;
    //std::vector<cv::Vec4i> hierarchy;
    //cv::findContours(binary, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //for (int i = 0; i < contours.size(); i++) {
    //    std::cout << i << '\n';
    //    for (int j = 0; j < contours[i].size(); j++) {
    //        std::cout << contours[i][j].y << ' ' << contours[i][j].x << '\n';
    //    }
    //}

    //cv::Mat copy = img.clone();
    //cv::drawContours(copy, contours, -1, cv::Scalar(0, 255, 0), 1);
    //std::cout << copy.type();

    /*std::vector<std::pair<int, int>> coords;
    for (int i = 0; i < copy.rows; i++) {
        for (int j = 0; j < copy.cols; j++) {
            if (copy.at<cv::Vec3b>(i, j)[1] == 255 && copy.at<cv::Vec3b>(i, j)[0] == 0 && copy.at<cv::Vec3b>(i, j)[2] == 0) {
                auto coord = std::make_pair(i, j);
                coords.push_back(coord);
            }
        }
    }

    for (int i = 0; i < coords.size(); i++) {
        std::cout << coords[i].first << ' ' << coords[i].second << '\n';

    }*/


    //std::cout << (int) copy.at<cv::Vec3b>(0, 0)[0] << ' ' << (int) copy.at<cv::Vec3b>(0, 0)[1] << ' ' << (int) copy.at<cv::Vec3b>(0, 0)[2];
    //cv::imshow("None approximation", copy);
    //cv::imwrite("ura.jpg", copy);

    //cv::imshow("None approximation", binary);
    //cv::waitKey(0);

    //for (int i = 0; i < binary.rows; i++) {
    //    for (int j = 0; j < binary.cols; j++) {
    //        if (binary.at<uchar>(i, j) != 0) {
    //            std::cout << (int) binary.at<uchar>(i, j) << '\n';
    //        }
    //    }
    //    std::cout << '\n';
    //}




    //cv::imshow("test", test_img);
    //cv::imwrite("new.jpg", grayscale_img);
    //cv::waitKey(0);

    /*int delay = 1;

    cv :: namedWindow("Test", cv :: WINDOW_NORMAL);

    for (std :: size_t i = 0; i < slices.size(); ++i)
    {
        auto s = slices_top[i];
        cv :: imshow("Test", s);
        cv :: waitKey(delay);
    }

    cv :: destroyWindow("Test");*/


    //int n = 0;
    //std::cin >> n;
    //Graph graph = Graph(n);
    //int leaves = graph.CountGraphLeaves();
    //std::cout << leaves;
    return 0;
}
