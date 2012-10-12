#ifndef FREQ_VECTOR_H
#define FREQ_VECTOR_H

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "math.h"

#include <iostream>
#include <fstream>

#define SECTOR_NUM 8


using namespace std;

class freq_vector
{
public:

    double theta_dist[SECTOR_NUM];
    double phi_dist[SECTOR_NUM];

    freq_vector();

    ~freq_vector();

    freq_vector(double theta[], double phi[]);

    freq_vector(char *vect_file, int p);

    double compare_vector(freq_vector *templ);

    void sector_compare(char *temp, char *file);

};

extern void make_vector_file(char *file, char *out);



#endif // FREQ_VECTOR_H
