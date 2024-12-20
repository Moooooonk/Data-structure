#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

// Node structure for linked list
template<typename T>
struct Node {
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

// Linked list class
template<typename T>
class LinkedList {
public:
    Node<T>* head;

    LinkedList() : head(nullptr) {}

    void append(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() const {
        Node<T>* temp = head;
        while (temp) {
            cout << "(" << temp->data.x << ", " << temp->data.y << ", " << temp->data.z << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// Vector3D structure for 3D operations
struct Vector3D {
    double x, y, z;

    Vector3D(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Vector3D operator+(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double norm() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3D operator-(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }
};

// Comparator for Max Heap based on speed
struct Compare {
    bool operator()(const pair<int, double>& p1, const pair<int, double>& p2) {
        return p1.second < p2.second; // Max Heap
    }
};

// Function to evaluate a polynomial at t
double evaluatePolynomial(const vector<double>& coef, double t) {
    double result = 0;
    for (int i = 0; i < coef.size(); ++i) {
        result += coef[i] * pow(t, i);
    }
    return result;
}

// Function to calculate the first derivative of a polynomial
vector<double> differentiate(const vector<double>& coef) {
    vector<double> deriv(coef.size() - 1);
    for (int i = 1; i < coef.size(); ++i) {
        deriv[i - 1] = coef[i] * i;
    }
    return deriv;
}

// Calculate distance between two points
double calculateDistance(const Vector3D& p1, const Vector3D& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

// Calculate angle between two vectors
double calculateAngle(const Vector3D& v1, const Vector3D& v2) {
    double dotProduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    double norms = v1.norm() * v2.norm();
    return acos(dotProduct / norms) * (180.0 / M_PI); // Angle in degrees
}

// Calculate Frenet Frame components and curvatures
void calculateFrenetFrame(const vector<double>& coef_x, const vector<double>& coef_y, const vector<double>& coef_z, double t) {
    vector<double> dx = differentiate(coef_x);
    vector<double> dy = differentiate(coef_y);
    vector<double> dz = differentiate(coef_z);

    vector<double> ddx = differentiate(dx);
    vector<double> ddy = differentiate(dy);
    vector<double> ddz = differentiate(dz);

    Vector3D r_prime(evaluatePolynomial(dx, t), evaluatePolynomial(dy, t), evaluatePolynomial(dz, t));
    Vector3D r_double_prime(evaluatePolynomial(ddx, t), evaluatePolynomial(ddy, t), evaluatePolynomial(ddz, t));

    Vector3D tangent = r_prime * (1.0 / r_prime.norm());
    Vector3D normal = (r_double_prime - tangent * (r_double_prime.norm() / r_prime.norm())) * (1.0 / r_double_prime.norm());
    Vector3D binormal = Vector3D(
        tangent.y * normal.z - tangent.z * normal.y,
        tangent.z * normal.x - tangent.x * normal.z,
        tangent.x * normal.y - tangent.y * normal.x
    );

    double curvature = r_prime.norm() / pow(r_prime.norm(), 3);
    double torsion = (r_prime.x * r_double_prime.y * ddz[0] + r_prime.y * r_double_prime.z * ddx[0] + r_prime.z * r_double_prime.x * ddy[0]) / pow(r_prime.norm(), 2);

    cout << "At t = " << t << ":\n";
    cout << "  Tangent Vector: (" << tangent.x << ", " << tangent.y << ", " << tangent.z << ")\n";
    cout << "  Normal Vector: (" << normal.x << ", " << normal.y << ", " << normal.z << ")\n";
    cout << "  Binormal Vector: (" << binormal.x << ", " << binormal.y << ", " << binormal.z << ")\n";
    cout << "  Curvature: " << curvature << "\n";
    cout << "  Torsion: " << torsion << "\n";
}

struct Function {
    vector<double> coef_x, coef_y, coef_z;
    int degree;
    LinkedList<Vector3D> coordinates;
};

int main() {
    vector<Function> functions;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add Function" << endl;
        cout << "2. Remove Function" << endl;
        cout << "3. Display All Functions" << endl;
        cout << "4. Analyze Specific Function" << endl;
        cout << "5. Compare All Functions" << endl;
        cout << "6. Analyze Frenet Frame" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            Function func;
            cout << "Enter the degree of the polynomial: ";
            cin >> func.degree;

            func.coef_x.resize(func.degree + 1);
            func.coef_y.resize(func.degree + 1);
            func.coef_z.resize(func.degree + 1);

            cout << "Enter coefficients for x(t) from highest degree to constant: ";
            for (int i = func.degree; i >= 0; --i) cin >> func.coef_x[i];

            cout << "Enter coefficients for y(t) from highest degree to constant: ";
            for (int i = func.degree; i >= 0; --i) cin >> func.coef_y[i];

            cout << "Enter coefficients for z(t) from highest degree to constant: ";
            for (int i = func.degree; i >= 0; --i) cin >> func.coef_z[i];

            cout << "Enter range of t values (start, end, step): ";
            double t_start, t_end, t_step;
            cin >> t_start >> t_end >> t_step;

            for (double t = t_start; t <= t_end; t += t_step) {
                double x = evaluatePolynomial(func.coef_x, t);
                double y = evaluatePolynomial(func.coef_y, t);
                double z = evaluatePolynomial(func.coef_z, t);
                func.coordinates.append(Vector3D(x, y, z));
            }

            functions.push_back(func);
            cout << "Function added successfully!" << endl;
        } else if (choice == 2) {
            int index;
            cout << "Enter the index of the function to remove (1-based): ";
            cin >> index;

            if (index > 0 && index <= functions.size()) {
                functions.erase(functions.begin() + index - 1);
                cout << "Function removed successfully!" << endl;
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 3) {
            if (functions.empty()) {
                cout << "No functions available!" << endl;
            } else {
                for (int i = 0; i < functions.size(); ++i) {
                    cout << "Function " << i + 1 << " (Degree: " << functions[i].degree << "):" << endl;
                    cout << "Coordinates: ";
                    functions[i].coordinates.display();
                }
            }
        } else if (choice == 4) {
            int index;
            double t;
            cout << "Enter the index of the function to analyze (1-based): ";
            cin >> index;
            cout << "Enter the value of t: ";
            cin >> t;

            if (index > 0 && index <= functions.size()) {
                Function& func = functions[index - 1];

                double x = evaluatePolynomial(func.coef_x, t);
                double y = evaluatePolynomial(func.coef_y, t);
                double z = evaluatePolynomial(func.coef_z, t);

                double speed = Vector3D(
                    evaluatePolynomial(differentiate(func.coef_x), t),
                    evaluatePolynomial(differentiate(func.coef_y), t),
                    evaluatePolynomial(differentiate(func.coef_z), t)
                ).norm();

                cout << "At t = " << t << ", Position: (" << x << ", " << y << ", " << z << "), Speed: " << speed << endl;
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 5) {
            if (functions.size() < 2) {
                cout << "Need at least two functions to compare!" << endl;
            } else {
                double t;
                cout << "Enter the value of t: ";
                cin >> t;

                priority_queue<pair<int, double>, vector<pair<int, double>>, Compare> maxHeap;

                for (int i = 0; i < functions.size(); ++i) {
                    double speed = Vector3D(
                        evaluatePolynomial(differentiate(functions[i].coef_x), t),
                        evaluatePolynomial(differentiate(functions[i].coef_y), t),
                        evaluatePolynomial(differentiate(functions[i].coef_z), t)
                    ).norm();
                    maxHeap.push({i + 1, speed});
                }

                cout << "Maximum speed at t = " << t << " is by Function " << maxHeap.top().first << " with Speed: " << maxHeap.top().second << endl;

                for (int i = 0; i < functions.size(); ++i) {
                    for (int j = i + 1; j < functions.size(); ++j) {
                        Vector3D p1(
                            evaluatePolynomial(functions[i].coef_x, t),
                            evaluatePolynomial(functions[i].coef_y, t),
                            evaluatePolynomial(functions[i].coef_z, t)
                        );
                        Vector3D p2(
                            evaluatePolynomial(functions[j].coef_x, t),
                            evaluatePolynomial(functions[j].coef_y, t),
                            evaluatePolynomial(functions[j].coef_z, t)
                        );

                        double distance = calculateDistance(p1, p2);
                        double angle = calculateAngle(p1, p2);

                        cout << "Distance between Function " << i + 1 << " and Function " << j + 1 << ": " << distance << endl;
                        cout << "Angle between Function " << i + 1 << " and Function " << j + 1 << ": " << angle << " degrees" << endl;
                    }
                }
            }
        } else if (choice == 6) {
            if (functions.empty()) {
                cout << "No functions available!" << endl;
            } else {
                int index;
                double t;
                cout << "Enter the index of the function to analyze (1-based): ";
                cin >> index;
                cout << "Enter the value of t: ";
                cin >> t;

                if (index > 0 && index <= functions.size()) {
                    calculateFrenetFrame(functions[index - 1].coef_x, functions[index - 1].coef_y, functions[index - 1].coef_z, t);
                } else {
                    cout << "Invalid index!" << endl;
                }
            }
        } else if (choice == 7) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}


