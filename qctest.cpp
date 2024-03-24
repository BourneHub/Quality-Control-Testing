// Author Name: Iftiar Mullah
// Project name: Quality Control Testing
// UID: 806212501

#include <iostream>
#include <string>
#include <cctype> // For isdigit function
#include <cassert> // For assert function

using namespace std;

// Function to check if the input string is a valid QC result
bool isValidQC(string result) {
    if (result.empty()) {
        return false; // Returns false if string is empty
    }

    int i = 0, n = result.size();
    while (i < n) {
        if (result[i] != 'Q') {
            return false; // Returns false if each batch does not start with 'Q'
        }
        i++;

        int totalTests = 0;
        bool passFound = false, defectFound = false;

        // Parsing the test results and counts
        while (i < n && isdigit(result[i])) {
            if (result[i] == '0' && totalTests == 0) {
                return false; 
            }
            totalTests = totalTests * 10 + (result[i++] - '0');
        }

        int passDefectCount = 0;

        // Parsing pass ('p') and defect ('d') counts
        while (i < n && (result[i] == 'p' or result[i] == 'd')) {
            char type = result[i];
            i++;

            if (i >= n || !isdigit(result[i])) {
                return false; // If no count is found after p or d, then returns false
            }

            int count = 0;
            while (i < n && isdigit(result[i])) {
                if (result[i] == '0' && count == 0) {
                    if (i + 1 < n && isdigit(result[i + 1])) {
                        return false; 
                    }
                }
                count = count * 10 + (result[i++] - '0');
            }

            passDefectCount += count;

            if (type == 'p') {
                if (passFound) { 
                    return false;
                }
                passFound = true;
            }
            else {
                if (defectFound) {
                    return false;
                }
                defectFound = true;
            }
        }
        // The # of passes and defects must match the # of total tests 
        if (!passFound || !defectFound || passDefectCount != totalTests) {
            return false;
        }
    }
    return true;
}

// Function calculates total passes from the QC result
int passQC(string result)
{
    if (!isValidQC(result)) {
        return -1; // If string does not pass isValidQC function first, then returns -1
    }
    int sum = 0;
    for (int i = 0; i < result.size(); i++) // Loop iterates through string, looking for 'p' (passes)
    {
        if (result[i] != 'p')
        {
            continue; 
        }
        int p = 0;
        while (++i < result.size() && isdigit(result[i])) {
            p = (p * 10) + (result[i] - '0');
        }
        i--;
        sum += p;
    }
    return sum;
}

// Function calculates total defects from the QC result
int defectQC(string result)
{
    if (!isValidQC(result)) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < result.size(); i++) // Loop iterates through string, look for 'd' (defects)
    {
        if (result[i] != 'd')
        {
            continue;
        }
        int p = 0;
        while (++i < result.size() && isdigit(result[i])) {
            p = (p * 10) + (result[i] - '0');
        }
        i--;
        sum += p;
    }
    return sum;
}

// Function calculates total QC count from QC result
int totalQC(string result)
{
    if (!isValidQC(result)) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < result.size(); i++) // Loop iterates through string, looking for 'Q' (QC tests)
    {
        if (result[i] != 'Q')
        {
            continue;
        }
        int p = 0;
        while (++i < result.size() && isdigit(result[i])) {
            p = (p * 10) + (result[i] - '0');
        }
        i--;
        sum += p;
    }
    return sum;
}

// Function calculates total batches in string
int batches(string result) {
    if (!isValidQC(result)) {
        return -1;
    }
    int sum = 0;
        for (int i = 0; i < result.size(); i++) // Loop iterates through string, looking for how many Qs there are (indicates how many batches there are)
        {
            if (result[i] == 'Q')
            {
                sum += 1;
            }
        }
        return sum;
}

int main() {
    assert(isValidQC("Q1p1d0Q1p1d0Q1p1d0") == true);
    assert(isValidQC("Q5d2p3") == true);
    assert(isValidQC("q1p0d1") == false);
    assert(isValidQC("Q1pd1") == false);
    assert(isValidQC("Q1p1d") == false);
    assert(isValidQC("Q1p0d1 asdfs") == false);
    assert(isValidQC("Q5p00003d0002") == false);
    assert(isValidQC("Q5p0d0") == false);
    assert(isValidQC("Q0p0d0") == false);
    assert(isValidQC("Q4p1d3") == true);
    assert(isValidQC("Q5p0d0") == false);
    assert(isValidQC("Q5d2p3") == true);
    assert(isValidQC("Q4d2p2Q7d4p3") == true);
    assert(isValidQC("Q1d1p0Q1p0d1") == true);
    assert(isValidQC("Q1p1d0") == true);
    assert(isValidQC("Q5p1d4Q8d7p1") == true);
    assert(isValidQC("Q1p0d1Q1d0p1") == true);
    assert(isValidQC("Q5d2p3") == true);
    assert(isValidQC("Q5p3d2Q2p1d1") == true);
    assert(isValidQC("q1p0d1") == false);
    assert(isValidQC("Q1pd1") == false);
    assert(isValidQC("Q1p1d") == false);
    assert(isValidQC("Q1p0d1 asdfR") == false);
    assert(isValidQC("Q5p00003d0002") == false);
    assert(isValidQC("Q5p0d0") == false);
    assert(isValidQC("Q0p0d0") == false);
    assert(passQC("Q5p3d2Q2p1d1") == 4);
    assert(passQC("q1p0d1") == -1);
    assert(defectQC("Q5p3d2Q2p1d1") == 3);
    assert(defectQC("q1p0d1") == -1);
    assert(totalQC("Q5p3d2Q2p1d1") == 7);
    assert(totalQC("q1p0d1") == -1);
    assert(batches("Q2p1d1") == 1);
    assert(batches("Q5p3d2Q2p1d1") == 2);
    assert(batches("q1p0d1") == -1);
    assert(isValidQC("") == false);
    assert(isValidQC("  ") == false);
    assert(passQC("  ") == -1);
    assert(defectQC("   ") == -1);
    assert(totalQC("   ") == -1);
    assert(batches("   ") == -1);
    assert(isValidQC("Q2p1d1") == true);
    assert(passQC("Q2p1d1") == 1);
    assert(defectQC("Q2p1d1") == 1);
    assert(totalQC("Q2p1d1") == 2);
    assert(batches("Q2+1-1") == -1);
    assert(isValidQC("Q50p25d25") == true);
    assert(passQC("Q50p25d25") == 25);
    assert(defectQC("Q50d25p25") == 25);
    assert(batches("Q50d25p25") == 1);
    assert(totalQC("Q50d25p25") == 50);
    assert(isValidQC("Q50 p40d10") == false);
    assert(passQC("Q50p20p10") == -1);
    assert(isValidQC("Q1d1p0") == true);
    return 0;
}
