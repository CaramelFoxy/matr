#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    // Зчитування повної матриці
    vector<vector<double>> matrix(n, vector<double>(n));
    cout << "Enter the matrix elements:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    // Формування стиснутого формату (CSR - Rutherford-Boeing style)
    vector<double> vval;
    vector<int> vpos;
    // vptr має (n+1) елементів, останній елемент дає загальну кількість ненульових елементів
    vector<int> vptr(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        // Запам'ятовуємо початковий індекс для i-го рядка
        vptr[i] = vval.size();
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != 0) {
                vval.push_back(matrix[i][j]);
                vpos.push_back(j);
            }
        }
    }
    vptr[n] = vval.size();

    // Зчитування числа a
    double a;
    cout << "Enter the number a: ";
    cin >> a;

    // Обчислення matrix - aI використовуючи CSR-представлення
    // Для кожного рядка шукаємо діагональний елемент (кол index == row)
    for (int i = 0; i < n; ++i) {
        bool foundDiagonal = false;
        // Шукаємо в межах [vptr[i], vptr[i+1]) – існуючі ненульові елементи рядка
        for (int k = vptr[i]; k < vptr[i + 1]; ++k) {
            if (vpos[k] == i) {
                // Якщо діагональний елемент є, віднімаємо a
                vval[k] -= a;
                foundDiagonal = true;
                break;
            }
        }
        // Якщо діагональний елемент не знайдено, то його значення було 0
        // В результаті ми маємо отримати 0 - a = -a, і якщо -a не дорівнює нулю, треба вставити його
        if (!foundDiagonal && (-a != 0)) {
            // Знайдемо позицію для вставки, щоб зберегти впорядкування за стовпцями.
            // За умовчанням, якщо в рядку ще є елементи, шукаємо перший, у якого vpos > i.
            int insertPos = vptr[i + 1]; // за замовчуванням вставимо в кінець рядка
            for (int k = vptr[i]; k < vptr[i + 1]; ++k) {
                if (vpos[k] > i) {
                    insertPos = k;
                    break;
                }
            }
            // Вставка нового елемента у відповідне місце у vval та vpos
            vval.insert(vval.begin() + insertPos, -a);
            vpos.insert(vpos.begin() + insertPos, i);
            // Оновлюємо vptr для всіх наступних рядків
            for (int j = i + 1; j < vptr.size(); ++j) {
                vptr[j]++;
            }
        }
    }

    // Вивід результату
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
