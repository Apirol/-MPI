#include <iostream>
#include <mpi.h>
#include <vector>
#include <ctime>
#include <Windows.h>

const int Nmax = 10;
using namespace std;
std::vector <int> v(Nmax);

int main(int argc, char** argv)
{
	setlocale(LC_CTYPE, "Russian");
	int my_rank;
	int p;
	double source;
	long proc;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	long double r = 0;
	if (my_rank == 0)
	{
		for (int i = 1; i < p; i++)
		{
			MPI_Recv(&proc, 1, MPI_INT, MPI_ANY_SOURCE,
				1, MPI_COMM_WORLD, &status);
			MPI_Recv(&source, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE,
				0, MPI_COMM_WORLD, &status);
			std::cout << "Procces number = " << proc << "  The norms of vector are equal " << source << std::endl;
		}
		std::cout << "Total processes " << p << std::endl;
	}
	else
	{
		srand(time(NULL) + my_rank);
		long n = 0;
		for (int i = 0; i < Nmax; i++)
		{
			v[i] = rand() % 75;
			n += v[i] * v[i];
		}
		r = sqrt(n);
		MPI_Send(&r, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&my_rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
