#ifndef MATRIX_H
#define MATRIX_H

#include <QList>
#include <QStringList>
#include <stdexcept>
#include <QGenericMatrix>
#include "../calculable.h"
#include "../parser.h"
#include "../token.h"

class Matrix : public Calculable
{

public:

    /**
     * @brief constructor
     *
     * @param value - the string value
     */
    Matrix(QString value);

    /**
     * @brief Copy constructor
     *
     * @param value - the matrix
     */
    Matrix(Matrix &value);

    /**
     * @brief Construct a matrix of one per one with the value 0
     */
    Matrix();

    /**
     * @brief value accessor
     *
     * @return the value of the Calculable
     */
    QString getValue();

    /**
     * @brief Raw value accessor
     *
     * @return the raw value of the Calculable
     */
    QVector< QVector<double> > getRawValue();

    /**
     * @brief value setter
     *
     * @param newValue the value to set
     */
    void setValue(QString newValue);

    /**
     * @brief raw value setter
     *
     * @param newValue the value to set
     */
    void setRawValue(QVector< QVector<double> > newValue);

    /**
     * @brief Copy setter
     *
     * @param newValue the value to set
     */
    void setValue(Matrix *newValue);

    /**
     * @brief overload operator * between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator*(Calculable &a);

    /**
     * @brief overload operator - between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator+(Calculable &a);

    /**
     * @brief overload operator + between two Calculable
     *
     * @param a a Calculable
     * @return a Calculable
     */
    Calculable* operator-(Calculable &a);

    /**
     * @brief Get the number of rows of the matrix
     *
     * @return The number of rows
     */
    int getM();
    /**
     * @brief Get the number of columns of the matrix
     *
     * @return The number of columns
     */
    int getN();
    /**
     * @brief Set the number of rows of the matrix
     *
     * @param The new number of rows.
     */
    void setM(int M);
    /**
     * @brief Set the number of columns of the matrix
     *
     * @param The new number of columns.
     */
    void setN(int N);

    /**
     * @brief Get the raw value of cellule
     *
     * @param i - The row of the cell between 0 and M-1
     * @param j - The row of the cell between 0 and N-1
     * @return The raw value of the cellule
     */
    double getCell(const int i, const int j);

    /**
     * @brief Set the raw value of cellule
     *
     * @param i - The row of the cell between 0 and M-1
     * @param j - The row of the cell between 0 and N-1
     * @param value - The new raw value of the cellule
     */
    void setCell(const int i, const int j, const double value);

    /**
     * @brief Define the type of the element as a string
     */
     std::string getTypeStr();

    /**
     * @brief Define the type of the element as a TokenKind from token.h
     */
     TokenKind getType();

protected:
    /**
     * @brief Handle the matrix raw value
     */
    QVector< QVector<double> > value;

    /**
     * @brief Give the number of rows of the matrix
     */
    int M;

    /**
     * @brief Give the number of columns of the matrix
     */
    int N;
};

#endif // MATRIX_H
