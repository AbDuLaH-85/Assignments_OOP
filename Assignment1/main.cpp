#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include "bmplib.h"
using namespace std;

unsigned char imgGS[SIZE][SIZE] = {};
unsigned char imgGS2[SIZE][SIZE] = {};




void read_image()
{
    string imageName, path = "\\images\\";
    cout << "Enter the name that must be in imges folder: " << endl;
    cin >> imageName;
    path += imageName;
    char cwd[PATH_MAX];
    readGSBMP(strcat(getcwd(cwd, sizeof(cwd)), path.c_str()), imgGS);

}
 void Black_White_Filter()
{
    int sum = 0, count = 0, average;
    for (int i = 0;i <= SIZE; i++)
    {
        for (int j = 0;j <= SIZE;j++)
        {
            sum += imgGS[i][j];
            count++;
        }
    }
    average = (sum / count);
    for (int i = 0;i <= SIZE; i++)
    {
        for (int j = 0;j <= SIZE;j++)
        {
            if (imgGS[i][j] >= average)
            {
                imgGS[i][j] = 255;
            }
            else if (imgGS[i][j] < average)
            {
                imgGS[i][j] = 0;
            }
        }
    }
    showGSBMP(imgGS);

}
void  Invert_Filter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            imgGS[i][j] = 255 - imgGS[i][j];
        }

        }
    showGSBMP(imgGS);
}
void Merge_Filter() {
    char image_2_FileName[100];
    cout << "Enter the image 2 file name: ";
    cin >> image_2_FileName;
    readGSBMP(image_2_FileName, imgGS2);
    for (int i = 0;i < SIZE;i++)
    {
        for (int j = 0;j < SIZE;j++) {
            imgGS[i][j] = (imgGS[i][j] + imgGS2[i][j]) / 2;
        }
    }
    char imageFileName[100];
    cout << "Enter the image 1 file name: ";
    cin >> imageFileName;
    writeGSBMP(imageFileName, imgGS);
    showGSBMP(imgGS);
}
void Darken_and_Lighten_Image() {
    int choice;
    cout << "to be darker press 1 ,lighter press 2 : ";
    cin >> choice;
    while (choice == 1 || choice == 2)
    {
        if (choice == 1) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    imgGS[i][j] = imgGS[i][j] / 2;
                }
            }
            break;
        }
        else if (choice == 2) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    imgGS[i][j] = (imgGS[i][j] + 255) / 2;
                }
            }
            break;
        }

    }
    showGSBMP(imgGS);

}
void Flip_Image() {
    int choice;
    cout << "if you want to flip the image horizontally press1, vertically press2";
    cin >> choice;
    int tmp;
    while (choice == 1 || choice == 2) {
        if (choice == 1) {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE; j++) {
                    tmp = imgGS[i][j];
                    imgGS[i][j] = imgGS[SIZE - i][j];
                    imgGS[SIZE - i][j] = tmp;
                }
            }
            break;
        }

        else if (choice == 2) {
            for (int i = 0; i < SIZE / 2; i++) {
                for (int j = 0; j < SIZE; j++) {
                    tmp = imgGS[i][j];
                    imgGS[i][j] = imgGS[SIZE - i][j];
                    imgGS[SIZE - i][j] = tmp;
                }
            }
            for(int i=0;i<2;i++)
            {
                for (int i = 0; i < SIZE / 2; i++) {
                    for (int j = 0; j < SIZE / 2; j++) {
                        int temp = imgGS[i][j];
                        imgGS[i][j] = imgGS[SIZE - 1 - j][i];
                        imgGS[SIZE - 1 - j][i] = imgGS[SIZE - 1 - i][SIZE - 1 - j];
                        imgGS[SIZE - 1 - i][SIZE - 1 - j] = imgGS[j][SIZE - 1 - i];
                        imgGS[j][SIZE - 1 - i] = temp;
                    }
                }
            }
            break;
        }
    }
    showGSBMP(imgGS);
}
void Rotate_Image() {
    char s[SIZE][SIZE];
    int rotate;
    cout << "to rotate 90 press 1, 180 press 2, 270 press 3: ";
    cin >> rotate;
    while (rotate) {
        for(int i =0; i<SIZE;i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                s[i][j]= imgGS[i][j];
            }

        }
        rotate--;
        for (int i=0; i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                imgGS[i][j]=s[SIZE - j- 1][i];
            }
        }
    }



    showGSBMP(imgGS);
}
void filters()
{
    char choice;
    read_image();
    cout << "1- Black & White Filter\n2- Invert Filter\n3- Merge Filter \n4- Flip Image\n5- Darken and Lighten Image \n6- Rotate Image \n 0- end";
    cout << endl;
    cin >> choice;
    while (choice != '0') {
        if (choice == '1') {
            Black_White_Filter();
        }
        else if (choice == '2') {
            Invert_Filter();
        }
        else if (choice == '3') {
            Merge_Filter();
        }
        else if (choice == '4') {
            Flip_Image();
        }
        else if (choice == '5') {
            Darken_and_Lighten_Image();
        }
        else if (choice == '6') {
            Rotate_Image();
        }

        cout << "Enter the filter you want or 0 to exit " << endl;
        cout << "1- Black & White Filter\n2- Invert Filter\n3- Merge Filter \n4- Flip Image\n5- Darken and Lighten Image \n0-end";
        cout << endl;
        cin >> choice;
    }
    cout << "End" << endl;
}









 int main() {
    filters();
     return 0;

 }