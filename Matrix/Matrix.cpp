// Matrix.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
const float maxValue = 100.0;

struct Matrix {
	float ** matrix;
	int n;
	int m;
};

void buildMatrix(int n, int m, Matrix *matrix) {
	matrix->n = n;
	matrix->m = m;
	int i;

	if ((matrix->matrix = (float**)malloc(n * sizeof(float*))) == NULL)
	{
		cout << "Error al alojar la memoria de n";
	}

	for (i = 0; i<n; i++) {
		if ((matrix->matrix[i] = (float*)malloc(m * sizeof(float))) == NULL)
		{
			cout << "Error al alojar la memoria de m";
		}
	}
}

void randomMatrix(Matrix *matrix) {
	int i, j;
	for (i = 0; i<matrix->n; i++) {
		for (j = 0; j<matrix->m; j++) {
			//matrix->matrix[i][j]= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));
			matrix->matrix[i][j] = rand() % 100;
		}
	}
}

void printMatrix(Matrix *matrix) {
	int i, j;
	for (i = 0; i<matrix->n; i++) {
		cout << "\n";
		for (j = 0; j<matrix->m; j++) {
			cout << matrix->matrix[i][j];
			cout << "\t";
		}
	}
}

void sumMatrix(const Matrix*addend1, const Matrix*addend2, Matrix*result) {

	buildMatrix(addend1->n, addend2->n, result);

	if (addend1->n == addend2->n && addend1->m == addend2->m) {
		for (int i = 0; i<addend1->n; i++) {
			for (int j = 0; j<addend2->m; j++) {
				result->matrix[i][j] = addend1->matrix[i][j] + addend2->matrix[i][j];
			}
		}
	}

	else {
		cout << "Las matrices no son del mismo tamaño" << endl;
	}
}

void multMatrix(const Matrix*matrix1, const Matrix*matrix2, Matrix*result) {

	buildMatrix(matrix1->n, matrix2->m, result);


	for (int i = 0; i<matrix1->n; ++i) {
		for (int j = 0; j<matrix2->m; ++j) {
			for (int k = 0; k<matrix2->n; ++k) {
				result->matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
			}
		}
	}
}

void transposeMatrix(const Matrix *matrix, Matrix *result) {
	buildMatrix(matrix->m, matrix->n, result);

	for (int i = 0; i<matrix->m; i++) {
		for (int j = 0; j<matrix->n; j++) {
			result->matrix[i][j] = matrix->matrix[j][i];
		}
	}
}

int getValue(Matrix *lower, Matrix *upper, Matrix *reference, int i, int j, int n, bool isUpper) {
	int sum = reference->matrix[i][j];
		if (isUpper) {
			for (int k = 0; k < n; k++) {
				if(k != j){
					sum -= lower->matrix[i][k] * upper->matrix[k][i];
				}
			}
			sum = sum / lower->matrix[i][j];
		}
		else {
			for (int k = 0; k < n; k++) {
				if (k != i) {
					sum -= lower->matrix[i][k] * upper->matrix[k][i];
				}
			}
			sum = sum / upper->matrix[i][j];
		}
	return sum;
}

void diagMatrix(Matrix *reference, Matrix *upperTriangle) {

	if (reference->m != reference->n) {
		cout << "La matriz debe ser cuadrada para ser diagonalizable";
		return;
	}

	Matrix lowerTriangle;
	buildMatrix(reference->n, reference->m, &lowerTriangle);
	buildMatrix(reference->n, reference->m, upperTriangle);

	for (int i = 0; i<reference->n; i++) {
		for (int j = 0; j<i; j++) {
			upperTriangle->matrix[i][j] = 0;
		}
	}

	for (int i = 0; i<reference->n; i++) {
		for (int j = i; j<reference->m; j++) {
			if (i == j) {
				lowerTriangle.matrix[i][j] = 1;
			}
			else {
				lowerTriangle.matrix[i][j] = 0;
			}

		}
	}


	printMatrix(&lowerTriangle);
	cout << "\n+++++++++++++++++++++++++\n";
	printMatrix(upperTriangle);


	int j = 0;
	while (j < reference->m) {
		for (int i = 0; i<reference->n; i++) {
			if (j >= i) {
				upperTriangle->matrix[i][j] = getValue(&lowerTriangle, upperTriangle, reference, i, j, reference->n, true);
			}
			else {
				lowerTriangle.matrix[i][j] = getValue(&lowerTriangle, upperTriangle, reference, i, j, reference->n, false);
			}
			j++;
		}
	}
	cout << "\n+++++++++++++++++++++++++\n";
	printMatrix(upperTriangle);

}


int main()
{
	srand((unsigned)time(NULL));
	Matrix matrix;
	//    Matrix m1;
	//    Matrix m2;
	Matrix mr;

	buildMatrix(3, 3, &matrix);
	//    buildMatrix(3,3,&m1);

	randomMatrix(&matrix);
	//    randomMatrix(&m1);

	printMatrix(&matrix);
	cout << "\n";

	// sumMatrix(&m1, &m2, &mr);
	//printMatrix(&mr);
	//cout << "\n";

	//multMatrix(&m1, &m2, &mr);
	//printMatrix(&mr);
	//cout << "\n";

	    //transposeMatrix(&matrix, &mr);
	    //printMatrix(&mr);
	cout << "\n";

	diagMatrix(&matrix, &mr);
	//    printMatrix(&mr);
	//    cout << "\n";
	cin.get();


	return 0;
}


//function res = Crout(A,b)
//disp('La matriz aumentada es: ');
//A=[A b']
//[m,n]=size(A);

//if (A(1,1)==0)
//    disp('La factorizacion no es posible');
//    return
//end

//L(:,1)= A(:,1);
//U(1,:)= A(1,1:m)/A(1,1);

//for i=1:m-1
//    for j=i+1:m
//        fprintf('\n eliminacion fila %g columna %g \n' ,j,i)
//        A(j,:)=A(j,:)-A(i,:)*A(j,i)/A(i,i);
//        disp(A);
//        pause();
//    end
//    L(i+1:m,i+1)=A(i+1:m,i+1);
//    U(i+1,i:m)=A(i+1,i:m)/(A(i+1,i+1));
//end
