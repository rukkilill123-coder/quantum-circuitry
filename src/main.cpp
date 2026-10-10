#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>

/*

BASIC TODO:

    implement matrices (and vectors)
    implement kronecker and matmul
    implement gates
    implement a quantum algorithm
    use smaller int types and optimize 
    modularize
    safety rails matrix operations

*/

template <size_t r, size_t c>
class Matrix
{
    public:
    
        size_t rows{0};
        size_t columns{0};
    
        int array[r][c];

        Matrix() : rows(r), columns(c)
        {
            std::memset(this->array, 0, sizeof(this->array));
        }
        

        Matrix(const int (&array)[r][c]) : rows(r), columns(c)
        {
            std::copy(&array[0][0], &array[0][0] + r * c, &this->array[0][0]);
        }

        template <size_t operand_r, size_t operand_c>
        Matrix<r, operand_c> get_product(Matrix<operand_r, operand_c> operand)
        {
            Matrix<r, operand_c> product;

            for (size_t i{0}; i < this->rows; i++) 
            {
                for (size_t j{0}; j < operand.columns; j++)
                {
                    for (size_t k{0}; k < operand.rows; k++) 
                    {
                        product.array[i][j] += this->array[i][k] * operand.array[k][j];
                    }
                }
            }

            return product;
        }
        
        template <size_t operand_r, size_t operand_c>
        Matrix<r * operand_r, c * operand_c> get_kroneckers_product(Matrix<operand_r, operand_c> operand)
        {
            Matrix<r * operand_r, c * operand_c> product;

            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->columns; j++)
                {
                    for (size_t k = 0; k < operand.rows; k++)
                    {
                        for (size_t l = 0; l < operand.columns; l++)
                        {
                            product.array[i * operand_r + k][j * operand_c + l] = this->array[i][j] * operand.array[k][l];
                        }
                    }
                }
            }

            return product;
        }

        std::string get_shape()
        {
            return std::to_string(this->rows) + "x" + std::to_string(this->columns);
        }

        void print_matrix()
        {
            for (int i{0}; i < this->rows; i++)
            {
                for (int j{0}; j < this->columns; j++)
                {
                    char separator = ((j + 1) % columns == 0) ? '\n' : ' ';

                    std::cout << std::to_string(this->array[i][j]) + separator;
                }
            }
        }
};


int main()
{   
    /* Matrix m(
        {
            {5, 1, 2, 3, 1},
            {6, 7, 8, 2, 1},
            {5, 5, 5, 5, 5},
            {5, 1, 2, 4, 2}
        }
    );

    std::cout << m.get_shape() << std::endl; */





    /*Matrix m1(
    {
        {5, 1, 2, 3, 1},
        {6, 7, 8, 2, 1},
        {5, 5, 5, 5, 5},
        {5, 1, 2, 4, 2}
    });
    
    
    Matrix m2(
    {
        {5, 1, 2, 3, 1},
        {6, 7, 8, 2, 1},
        {5, 5, 5, 5, 5},
        {5, 1, 2, 4, 2},
        {1, 2, 3, 4, 5}
    });
    
    Matrix m3 = m1.get_product(m2);

    m3.print_matrix();*/




    /*Matrix m1(
    {
        {1, 1},
        {1, 1}
    });
    
    
    Matrix m2(
    {
        {1, 0},
        {0, 1}
    });
    
    Matrix m3 = m1.get_kroneckers_product(m2);

    m3.print_matrix();*/


    return 0;
}