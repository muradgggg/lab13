#include <iostream>
#include <fstream>

template <typename T>
class Matrix {
private:
    int rows;       // Number of rows in the matrix
    int columns;    // Number of columns in the matrix
    T** values;     // 2D array to store the matrix elements

public:
    // Default constructor
    Matrix() : rows(0), columns(0), values(nullptr) {}

    // Parameterized constructor
    Matrix(int rows_t, int cols_t, T** data2) {
        rows = rows_t;
        columns = cols_t;
        values = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            values[i] = new T[columns];
            for (int j = 0; j < columns; ++j) {
                values[i][j] = data2[i][j];
            }
        }
    }

    // Copy constructor
    Matrix(const Matrix& other)  {
        rows = other.rows;
        columns = other.columns;
        values = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            values[i] = new T[columns];
            for (int j = 0; j < columns; ++j) {
                values[i][j] = other.values[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        if (rows > 0) {
            for (int i = 0; i < rows; ++i) {
                delete[] values[i];
            }
            delete[] values;
        }
    }

    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (&other == this) {
            return *this;
        }
        if (rows > 0) {
            for (int i = 0; i < rows; ++i) {
                delete[] values[i];
            }
            delete[] values;
        }
        rows = other.rows;
        columns = other.columns;
        values = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            values[i] = new T[columns];
            for (int j = 0; j < columns; ++j) {
                values[i][j] = other.values[i][j];
            }
        }
        return *this;
    }

    // Indexing operator
    T* operator[](int row) {
        return values[row];
    }

    // Matrix multiplication operator
    Matrix operator*(const Matrix& other) const {
        if (columns != other.rows) {
            std::cout << "Matrices have incompatible dimensions" << std::endl;
        }
        T** temp_ar;
        temp_ar = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            temp_ar[i] = new T[other.columns];
            for (int j = 0; j < other.columns; ++j) {
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(rows, other.columns, temp_ar);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                T sum = T();
                for (int k = 0; k < columns; ++k) {
                    sum += values[i][k] * other.values[k][j];
                }
                result[i][j] = sum;
            }
        }
        // Deallocate temporary array
        for (int i = 0; i < rows; ++i){
            delete[] temp_ar[i];
        }
        delete[] temp_ar;
        return result;
    }

    // Function to get the number of rows
    int getRows() const {
        return rows;
    }

    // Function to get the number of columns
    int getColumns() const {
        return columns;
    }

    // Function to display the matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << values[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Function to read a matrix from a file
template <typename T>
Matrix<T> readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Failed to open the file" << std::endl;
        return Matrix<T>();
    }
    int rows, columns;
    file >> rows >> columns;
    T** data = new T*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new T[columns];
        for (int j = 0; j < columns; ++j) {
            file >> data[i][j];
        }
    }
    file.close();
    return Matrix<T>(rows, columns, data);
}
int main() {
    // Read matrices from files
    Matrix<int> matrix1 = readMatrixFromFile<int>("matrix1.txt");
    Matrix<int> matrix2 = readMatrixFromFile<int>("matrix2.txt");

    // Perform matrix multiplication
    Matrix<int> result = matrix1 * matrix2;

    // Display the result
    result.display();
    return 0;
}