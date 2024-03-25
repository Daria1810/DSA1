#include <iostream>
#include <cmath>
#include "list1.h"

using namespace std;
///subpunctul a)
// definition for the data structure
struct Term
{
    float coefficient;
    int exponent;
};
struct
{
    float re, im;
}Complex;
///subpunctul b)
// Create a template class for a polynomial represented as a linked list of terms
template <typename T>
class Polynomial
{
public:
    LinkedList<T> terms;  // Store terms of the polynomial in a linked list

public:
    // Constructor
    Polynomial() {}

    // Method to add a term to the polynomial
    ///subpunctul c)
    void addTerm(Term t)
    {
        terms.addLast(t);
    }

    // Method to evaluate the polynomial for a given value of X
    ///subpunctul d)
    float evaluate(float x)
    {
        float result = 0;
        Node<T>* index = terms.pfirst;  // Start at the beginning of the list

        while (index != NULL)
        {
            result += index->info.coefficient * pow(x, index->info.exponent);
            index = index->next;  // Move to the next term
        }

        return result;
    }
    ///subpunctul e)
    // Method to add two polynomials and return the result as a new polynomial
    Polynomial <T> add(Polynomial<T> x)
    {
        Polynomial <T> addition;
        Node<T>* i = this->terms.pfirst;
        Node<T>* j = x.terms.pfirst;

        while (i != NULL && j!= NULL)
        {
            if (i->info.exponent > j->info.exponent)
            {
                addition.addTerm(i->info);
                i = i->next;
            }
            else if (i->info.exponent < j->info.exponent)
            {
                addition.addTerm(j->info);
                j = j->next;
            }
            else      // Exponents are equal, so add the coefficients and create a new term
            {
                float sum = i->info.coefficient + j->info.coefficient;
                if (sum != 0)
                {
                    Term t = {sum, i->info.exponent};
                    addition.addTerm(t);
                }
                i = i->next;
                j = j->next;
            }
        }

        // Add any remaining terms from either polynomial
        while (i!=NULL)
        {
            addition.addTerm(i->info);
            i = i->next;
        }
        while (j!=NULL)
        {
            addition.addTerm(j->info);
            j = j->next;
        }

        return addition;
    }
    ///subpunctul f)
    // Method to multiply two polynomials
    Polynomial<T> multiply(Polynomial<T> x)
{
    Polynomial<T> result;
    Node<T>* i = this->terms.pfirst;

    while (i != NULL)
    {
        Node<T>* j = x.terms.pfirst;

        while (j != NULL)
        {
            double coefficient = i->info.coefficient * j->info.coefficient;
            int exponent = i->info.exponent + j->info.exponent;

            // Check if a term with this exponent already exists in the result
            Node<T>* existingTerm = result.terms.pfirst;
            while (existingTerm != NULL)
            {
                if (existingTerm->info.exponent == exponent)
                {
                    existingTerm->info.coefficient += coefficient;
                    break;
                }
                existingTerm = existingTerm->next;
            }

            // If no term with this exponent exists yet, add a new one
            if (existingTerm == NULL)
            {
                Term newTerm;
                newTerm.coefficient = coefficient;
                newTerm.exponent = exponent;
                result.addTerm(newTerm);
            }

            j = j->next;
        }

        i = i->next;
    }

    return result;
}

    ///print the polynomial
    void print()
    {
        Node<T>* current = terms.pfirst;

        while (current != NULL)
        {
            if (current != terms.pfirst && current->info.coefficient >= 0)
            {
                cout << "+";  // Print "+" before positive terms (except the first term)
            }
            if (current->info.coefficient != 1 || current->info.exponent == 0)
            {
                cout << current->info.coefficient;  // Print coefficient (if not 1) for non-constant terms
            }
            if (current->info.exponent > 0)
            {
                cout << "x";
                if (current->info.exponent > 1)
                {
                    cout << "^" << current->info.exponent;  // Print exponent (if not 1 or 0) for non-constant terms
                }
            }
            current = current->next;
        }
    }
};
int main()
{


    cout<<"b)"<<endl;
    float coeff;
    int exp;
    int degree;
    cout<<"give the degree of the polynomial "; cin>>degree;
    Polynomial<Term> poly;
    for(int i=0;i<=degree;i++)
    {
        cout<<"give the coefficients and exponents "<<endl;
        cin>>coeff;
        cin>>exp;
        poly.addTerm({coeff,exp});
        }

    cout<<endl<<"c)"<<endl;
        poly.print();

    cout<<endl<<"d), e), f)";

    Polynomial<Term> p1, p2, sum, p3, p4, product, p5, sum2;
    p1.addTerm({2, 3});
    p1.addTerm({-1, 1});
    p1.addTerm({5, 0});

    p2.addTerm({-2, 3});
    p2.addTerm({3, 2});
    p2.addTerm({2, 0});

    p3.addTerm({1, 2});
    p3.addTerm({3, 1});

    p4.addTerm({2, 1});
    p4.addTerm({-5, 0});

    p5.addTerm({4, 3});
    p5.addTerm({-3, 2});
    p5.addTerm({2, 1});
    p5.addTerm({-1, 0});

    sum = p1.add(p2);

    ///sum2=p2.add(p3);
    sum.print();
    cout<<endl;
    ///sum2.print();


     product = p3.multiply(p4);
     product.print();  // Expected output: "2x^3-5x^2+6x^1-15x^0"
     cout<<endl;

    float x = 2;
    float value = p5.evaluate(x);
    cout << value << endl;  // Expected output: 23*/

    return 0;
}
