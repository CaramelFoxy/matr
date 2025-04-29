#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    // ���������� ����� �������
    vector<vector<double>> matrix(n, vector<double>(n));
    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    // ���������� ���������� ������� (CSR - Rutherford-Boeing style)
    vector<double> vval;
    vector<int> vpos;
    // vptr �� (n+1) ��������, ������� ������� �� �������� ������� ���������� ��������
    vector<int> vptr(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        // �����'������� ���������� ������ ��� i-�� �����
        vptr[i] = vval.size();
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                vval.push_back(matrix[i][j]);
                vpos.push_back(j);
            }
        }
    }
    vptr[n] = vval.size();

    // ���������� ����� a
    double a;
    cout << "Enter the number a: ";
    cin >> a;

    // ���������� matrix - aI �������������� CSR-�������������
    // ��� ������� ����� ������ ����������� ������� (��� index == row)
    for (int i = 0; i < n; ++i) {
        bool foundDiagonal = false;
        // ������ � ����� [vptr[i], vptr[i+1]) � ������� �������� �������� �����
        for (int k = vptr[i]; k < vptr[i + 1]; ++k) {
            if (vpos[k] == i) {
                // ���� ����������� ������� �, ������� a
                vval[k] -= a;
                foundDiagonal = true;
                break;
            }
        }
        // ���� ����������� ������� �� ��������, �� ���� �������� ���� 0
        // � ��������� �� ���� �������� 0 - a = -a, � ���� -a �� ������� ����, ����� �������� ����
        if (!foundDiagonal && (-a != 0)) {
            // �������� ������� ��� �������, ��� �������� ������������� �� ���������.
            // �� ����������, ���� � ����� �� � ��������, ������ ������, � ����� vpos > i.
            int insertPos = vptr[i + 1]; // �� ������������� �������� � ����� �����
            for (int k = vptr[i]; k < vptr[i + 1]; ++k) {
                if (vpos[k] > i) {
                    insertPos = k;
                    break;
                }
            }
            // ������� ������ �������� � �������� ���� � vval �� vpos
            vval.insert(vval.begin() + insertPos, -a);
            vpos.insert(vpos.begin() + insertPos, i);
            // ��������� vptr ��� ��� ��������� �����
            for (int j = i + 1; j < vptr.size(); ++j) {
                vptr[j]++;
            }
        }
    }

    // ���� ����������
    cout << "\nResult in format vval-vpos-vptr after computing matrix - aI:" << endl;
    cout << "vval: ";
    for (double val : vval)
        cout << val << " ";
    cout << "\nvpos: ";
    for (int pos : vpos)
        cout << pos << " ";
    cout << "\nvptr: ";
    for (int ptr : vptr)
        cout << ptr << " ";
    cout << endl;

    return 0;
}
