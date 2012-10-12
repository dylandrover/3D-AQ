#include <QtGui/QApplication>
#include "mainwindow.h"
#include "freq_vector.h"

#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    make_vector_file("set/sin", "sin_vect");
    freq_vector *sin = new freq_vector("sin_vect", 4);

    make_vector_file("set/zigzag", "zigzag_vect");
    freq_vector *zigzag = new freq_vector("zigzag_vect", 4);

    make_vector_file("set/spiral3d", "spiral_vect");
    freq_vector *spiral = new freq_vector("spiral_vect", 4);

    make_vector_file("set/spring", "spring_vect");
    freq_vector *spring = new freq_vector("spring_vect", 4);

    cout << spiral->compare_vector(sin) << endl;
    cout << spiral->compare_vector(zigzag) << endl;
    cout << spiral->compare_vector(spiral) << endl;
    cout << spiral->compare_vector(spring) << endl;


    return a.exec();
}
