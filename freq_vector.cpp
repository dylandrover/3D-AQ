#include <QtGui/QApplication>
#include "mainwindow.h"
#include "math.h"

#include "freq_vector.h"
#include <iostream>
#include <fstream>

using namespace std;

/**************************************************************
  * Constructor which sets the 2 arrays in a freq_vector object
  * to NULL
**************************************************************/
freq_vector::freq_vector()
{
    *theta_dist = NULL;
    *phi_dist = NULL;
}

/**************************************************************
  * Deconstructor
**************************************************************/
freq_vector::~freq_vector()
{
    delete theta_dist;
    delete phi_dist;
}

/**************************************************************
  * Constructor which allows the insertion of 2 arrays into the
  * place of the 2 arrays in a freq_vector object
**************************************************************/
freq_vector::freq_vector(double theta[], double phi[])
{
    for(int i = 0; i < SECTOR_NUM; i++)
    {
        theta_dist[i] = theta[i];
        phi_dist[i] = phi[i];
    }
}

/**************************************************************
  * Constructor that will take in a vector file, count the frequency
  * of each sector and then assign these value to a freq_vector
**************************************************************/
freq_vector::freq_vector(char *vect_file, int p)
{

    double freq_1[SECTOR_NUM] = {0};
    double freq_2[SECTOR_NUM] = {0};

    ifstream fin;
    fin.open(vect_file);

    double x, y, z;

    if(fin.is_open())
    {
        while(!fin.eof())
        {
            fin >> x >> y >> z;

            double theta_sec = 180+atan2(y, x)*180/3.14;
            double phi_sec = 180+atan2(z, x)*180/3.14;

            int sec_xy = int(p+theta_sec/(180/p))%(2*p);
            int sec_xz = int(p+phi_sec/(180/p))%(2*p);

            freq_1[sec_xy]++;
            freq_2[sec_xz]++;
        }
    }
    else
        cout << "error opening file" << endl;

    fin.close();

    for(int i = 0; i < SECTOR_NUM; i++)
    {
        theta_dist[i] = freq_1[i];
        phi_dist[i] = freq_2[i];
    }

}

/**************************************************************
  * Funtion that will compare a freq_vector object to another,
  * if there is a match in one vector it will add 0.5 to the
  * overall sum. In the end the sum will have a normalized between
  * 0 - 1, 1 being a complete match.
**************************************************************/
double freq_vector::compare_vector(freq_vector *templ)
{
    double sum = 0;

    for(int i = 0; i < SECTOR_NUM; i++)
    {
        if(this->theta_dist[i] == templ->theta_dist[i])
            sum += 0.5;
        if(this->phi_dist[i] == templ->phi_dist[i])
            sum += 0.5;
    }

    return (sum/8);
}


/**************************************************************
  * Vestigal Function
**************************************************************/
void freq_vector::sector_compare(char *temp, char *file)
{
    ifstream ftemp;
    ifstream input;
    ftemp.open(temp);
    input.open(file);

    double sum = 0;
    int count = 0;

    if(ftemp.is_open() && input.is_open())
    {
        while(!ftemp.eof() && !input.eof())
        {
            int theta_1, theta_2;
            int phi_1, phi_2;

            ftemp >> theta_1 >> phi_1;
            input >> theta_2 >> phi_2;

            if(theta_1 == theta_2)
                sum += 0.5;
            if(phi_1 == phi_2)
                sum += 0.5;

            count++;
        }
    }
    else
        cout << "error opening file";

    cout << sum/count << endl;

    ftemp.close();
    input.close();
}

/**************************************************************
  * Extern function that will translate a point file into a file
  * of vectors (suitable to pass to freq_vector constructor)
  * that  are the difference between adjecent points
**************************************************************/
void make_vector_file(char *file, char *out)
{
    ifstream fin;
    ofstream fout(out);
    fin.open(file);


    int point_1[3] = {0, 0, 0};
    int point_2[3] = {0, 0, 0};

    if(fin.is_open())
    {
        for(int i = 0; i < 3 ; i++)
        {
            fin >> point_1[i];
        }
        while(!fin.eof())
        {
            for(int i = 0; i < 3 ; i++)
            {
                fin >> point_2[i];
                fout << point_2[i] - point_1[i] << " ";
            }
            for(int i = 0; i < 3 ; i++)
            {
                point_1[i] = point_2[i];
            }
            fout << endl;

        }
    }
    else
        cout << "Error opening file";

    fin.close();
    fout.close();

}




