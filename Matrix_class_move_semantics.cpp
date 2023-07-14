#include <iostream>

class Matrix_class {

private:
    int** m_p;
    int m_row;
    int m_column;
public:
    Matrix_class();
    Matrix_class(int, int);
    Matrix_class(const Matrix_class& ob);
    Matrix_class& operator=(const Matrix_class& ob);

    Matrix_class(Matrix_class&& ob);    //move constructor
    Matrix_class& operator=(Matrix_class&& ob);    //move operator assignment

    ~Matrix_class();
    void changeRows(int, int);
    void changeColumns(int, int);
    void printMatrix();
    void initializeMatrix();
    void setRow(int);
    int getRow()const;
    void setColumn(int);
    int getColumn()const;
};


Matrix_class::Matrix_class()
{
    std::cout << "Default constructor\n";
    m_row = 0;
    m_column = 0;

    m_p = nullptr;
}

Matrix_class::Matrix_class(int r, int c) {
    m_row = r;
    m_column = c;

    m_p = new int* [m_row];

    for (int i = 0; i < m_row; i++)
    {
        m_p[i] = new int[m_column];
    }
}


void Matrix_class::setRow(int r)
{
    if (r <= 0)
    {
        throw std::invalid_argument("Invalid size");
    }
    m_row = r;
}

int Matrix_class::getRow()const
{
    return m_row;
}

void Matrix_class::setColumn(int c)
{
    if (c <= 0)
    {
        throw std::invalid_argument("Invalid size");
    }
    m_column = c;
}

int Matrix_class::getColumn()const
{
    return m_column;
}


Matrix_class::Matrix_class(const Matrix_class& ob)
{
    std::cout << "Copy constructor\n";
    this->m_row = ob.m_row;
    this->m_column = ob.m_column;

    this->m_p = new int* [m_row];

    for (int i = 0; i < m_row; i++)
    {
        this->m_p[i] = new int[m_column];
    }

    for (int i = 0; i < ob.m_row; i++)
    {
        for (int j = 0; j < ob.m_column; j++)
        {
            this->m_p[i][j] = ob.m_p[i][j];
        }
    }
}


Matrix_class::Matrix_class(Matrix_class&& ob)  //move constructor
{
    std::cout << "Move constructor\n";

    if (this != &ob)
    {
        this->m_row = ob.m_row;
        this->m_column = ob.m_column;

        this->m_p = ob.m_p;

        ob.m_row = 0;
        ob.m_column = 0;
        ob.m_p = nullptr;
    }
}


Matrix_class& Matrix_class::operator=(const Matrix_class& ob)
{
    std::cout << "Assignment operator\n";

    if (this != &ob)
    {
        this->m_row = ob.m_row;
        this->m_column = ob.m_column;

        delete[] m_p;
        this->m_p = new int* [m_row];

        for (int i = 0; i < m_row; i++)
        {
            this->m_p[i] = new int[m_column];
        }

        for (int i = 0; i < ob.m_row; i++)
        {
            for (int j = 0; j < ob.m_column; j++)
            {
                this->m_p[i][j] = ob.m_p[i][j];
            }
        }
    }
    return *this;
}


Matrix_class& Matrix_class::operator=(Matrix_class&& ob)  //move operator assignment
{
    std::cout << "Move " << __func__ << "\n";

    if (this != &ob)
    {
        for (int i = 0; i < this->m_row; i++)
        {
            delete[] this->m_p[i];
        }
        delete[] this->m_p;

        this->m_row = ob.m_row;
        this->m_column = ob.m_column;

        this->m_p = ob.m_p;

        ob.m_row = 0;
        ob.m_column = 0;
        ob.m_p = nullptr;
    }
    return *this;
}


Matrix_class::~Matrix_class()
{
    std::cout << "Destructor\n";

    for (int i = 0; i < m_row; i++)
    {
        delete[] m_p[i];
    }
    delete[] m_p;
}


void Matrix_class::initializeMatrix()
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            m_p[i][j] = rand() % 100 + 1;
        }
    }
}


void Matrix_class::changeRows(int k, int g)
{
    for (int i = 0; i <= m_column; i++)
    {
        int tmp = m_p[k][i];
        m_p[k][i] = m_p[g][i];
        m_p[g][i] = tmp;
    }
}


void Matrix_class::changeColumns(int k, int g)
{
    for (int i = 0; i < m_row; i++)
    {
        int tmp = m_p[i][k];
        m_p[i][k] = m_p[i][g];
        m_p[i][g] = tmp;
    }
}


void Matrix_class::printMatrix()
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_column; j++)
        {
            std::cout << "p[" << i << "][" << j << "] = " << m_p[i][j] << "\n";
        }
    }
}


int main()
{
    int size;
    Matrix_class ob;

    std::cout << "Enter the size of a matrix\n";
    std::cin >> size;

    Matrix_class ob1(size, size);

    try {
        ob1.getRow();
        ob1.setRow(size);
    }
    catch (const std::invalid_argument ia)
    {
        std::cerr << ia.what() << std::endl;
    }

    try {
        ob1.getColumn();
        ob1.setColumn(size);
    }
    catch (const std::invalid_argument ia)
    {
        std::cerr << ia.what() << std::endl;
    }

    std::cout << "Before Swap\n";
    ob1.initializeMatrix();
    ob1.printMatrix();
    std::cout << "Swapping colums\n";
    ob1.changeColumns(0, 2);
    ob1.printMatrix();
    std::cout << "Swapping m_rows\n";
    ob1.changeRows(0, 2);
    ob1.printMatrix();

    Matrix_class ob_cp(ob1);
    ob_cp.printMatrix();

    ob = ob_cp;

    //move semantics
    Matrix_class m_ob(4, 5);
    m_ob = std::move(Matrix_class(2, 3));

    Matrix_class m_ob1 = std::move(Matrix_class(6, 7));

    return 0;
}
