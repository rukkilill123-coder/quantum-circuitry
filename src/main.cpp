#include <type_traits>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

/*

BASIC TODO:

    implement gates
    implement a quantum algorithm
    use smaller int types and optimize 
    modularize
    safety rails matrix operations
    store on the heap
    matrix method params are copied, very bad
    add more comments explaining certain design choices
    find a better place to store your tests
    gpu acceleration?
    syntax is an eyesore in some places
    
*/

template <size_t r, size_t c>
class Matrix
{
    public:
    
        size_t rows{0};
        size_t columns{0};
    
        float array[r][c];

        Matrix() : rows(r), columns(c)
        {
            std::memset(this->array, 0, sizeof(this->array));
        }
        

        Matrix(const float (&array)[r][c]) : rows(r), columns(c)
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

        template<size_t exp>
        auto get_kronecker_power()
        {
            if constexpr (exp == 1)
            {
                return *this;
            }
            else
            {
                return this->get_kroneckers_product(this->get_kronecker_power<exp - 1>());
            }
        }

        template<typename t>
        Matrix<r, c> operator+(t operand)
        {
            Matrix<r, c> sum;

            if constexpr (std::is_integral_v<t>)
            {
                for (int i = 0; i < this->rows; i++)
                {
                    for (int j = 0; j < this->columns; j++) 
                    {
                        sum.array[i][j] += this->array[i][j] + operand;
                    }
                }
            }
            else
            {
                for (int i = 0; i < this->rows; i++)
                {
                    for (int j = 0; j < this->columns; j++) 
                    {
                        sum.array[i][j] += this->array[i][j] + operand.array[i][j];
                    }
                }
            }

            return sum;
        }

        Matrix<r, c> operator*(float scalar)
        {
            Matrix<r, c> scaled;

            for (int i = 0; i < this->rows; i++)
            {
                for (int j = 0; j < this->columns; j++)
                {
                    scaled.array[i][j] = this->array[i][j] * scalar;
                }
            }

            return scaled;
        }


        std::string get_shape()
        {
            return std::to_string(this->rows) + "x" + std::to_string(this->columns);
        }

        void print()
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

constexpr unsigned int get_log2(unsigned int base)
{
    unsigned int exponent = 0;

    while (base > 1)
    {
        base /= 2;
        exponent++;
    }

    return exponent;
}


template <size_t rows = 2>
class Qubit : public Matrix<rows, 1>
{
    public:
        Qubit() 
        {
            this->array[0][0] = 1; 
            this->array[1][0] = 0;
        }

        Qubit(const float (&array)[rows][1]) : Matrix<rows, 1>(array) {}

        Qubit(Matrix<rows, 1> mat) : Matrix<rows, 1>(mat) {}        

        Qubit<rows> get_hadamard()
        {
            constexpr unsigned int n = get_log2(rows);

            Matrix<2, 2> H = Matrix(
                {
                    {1, 1},
                    {1, -1}
                }
            ) * (1/sqrt(2));

            return (H.get_kronecker_power<n>()).get_product(*this);
        }

        Qubit<rows> get_NOT()
        {
            constexpr unsigned int n = get_log2(rows);

            Matrix<2, 2> NOT = Matrix(
                {
                    {0, 1},
                    {1, 0}
                }
            );

            return (NOT.get_kronecker_power<n>()).get_product(*this);
        }

        /*Qubit<rows> get_CNOT(unsigned int controll, unsigned int target)
        {
            
        }*/
};


int main()
{
    
    return 0;
}