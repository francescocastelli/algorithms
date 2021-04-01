#include <iostream>
#include <numeric>
#include <random>
#include <bits/stdc++.h> 

//BINARY SEARCH
static int binarySearch(std::vector<int> &v, int lower, int upper, int el)
{
    if ( upper >= lower )
    {
        int middle = int((upper-lower)/2 + lower);

        if ( v[middle] == el ) 
            return middle;

        if ( el < v[middle] )
            return binarySearch(v, lower, upper=middle-1, el);
        else 
            return binarySearch(v, middle+1, upper, el);
    }

    return -1;
}

//POWERING A NUMBER 
//
static int numberPowering(int a, int n)
{
    if ( n == 1 ) return a;

    int t; 

    if ( n % 2 == 0)
    {
       t = numberPowering(a, n/2);
       return t*t; 
    }

    t = numberPowering(a, (n-1)/2);
    return t * t * a;    
}

//STRASSEN MATRIX MULTIPLICATION
//taken from a web site
using namespace std; 
typedef long long lld;

static lld** MatrixMultiply(lld** a, lld** b, int n, int l, int m) 
{ 
    lld** c = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        c[i] = new lld[m]; 
  
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) { 
            c[i][j] = 0; 
            for (int k = 0; k < l; k++) { 
                c[i][j] += a[i][k] * b[k][j]; 
            } 
        } 
    } 
    return c; 
}

static lld** Strassen(lld** a, lld** b, int n, int l, int m) 
{ 
    if (n == 1 || l == 1 || m == 1)  
        return MatrixMultiply(a, b, n, l, m);

    lld** c = new lld*[n]; 
    for (int i = 0; i < n; i++) 
        c[i] = new lld[m]; 
  
    int adjN = (n >> 1) + (n & 1); 
    int adjL = (l >> 1) + (l & 1); 
    int adjM = (m >> 1) + (m & 1); 
  
    lld**** As = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        As[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            As[x][y] = new lld*[adjN]; 
            for (int i = 0; i < adjN; i++) { 
                As[x][y][i] = new lld[adjL]; 
                for (int j = 0; j < adjL; j++) { 
                    int I = i + (x & 1) * adjN; 
                    int J = j + (y & 1) * adjL; 
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0; 
                } 
            } 
        } 
    } 
  
    lld**** Bs = new lld***[2]; 
    for (int x = 0; x < 2; x++) { 
        Bs[x] = new lld**[2]; 
        for (int y = 0; y < 2; y++) { 
            Bs[x][y] = new lld*[adjN]; 
            for (int i = 0; i < adjL; i++) { 
                Bs[x][y][i] = new lld[adjM]; 
                for (int j = 0; j < adjM; j++) { 
                    int I = i + (x & 1) * adjL; 
                    int J = j + (y & 1) * adjM; 
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0; 
                } 
            } 
        } 
    } 
  
    lld*** s = new lld**[10]; 
    for (int i = 0; i < 10; i++) { 
        switch (i) { 
        case 0: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 1: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] + As[0][1][j][k]; 
                } 
            } 
            break; 
        case 2: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k]; 
                } 
            } 
            break; 
        case 3: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k]; 
                } 
            } 
            break; 
        case 4: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] + As[1][1][j][k]; 
                } 
            } 
            break; 
        case 5: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 6: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][1][j][k] - As[1][1][j][k]; 
                } 
            } 
            break; 
        case 7: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k]; 
                } 
            } 
            break; 
        case 8: 
            s[i] = new lld*[adjN]; 
            for (int j = 0; j < adjN; j++) { 
                s[i][j] = new lld[adjL]; 
                for (int k = 0; k < adjL; k++) { 
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k]; 
                } 
            } 
            break; 
        case 9: 
            s[i] = new lld*[adjL]; 
            for (int j = 0; j < adjL; j++) { 
                s[i][j] = new lld[adjM]; 
                for (int k = 0; k < adjM; k++) { 
                    s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k]; 
                } 
            } 
            break; 
        } 
    } 
  
    lld*** p = new lld**[7]; 
    p[0] = Strassen(As[0][0], s[0], adjN, adjL, adjM); 
    p[1] = Strassen(s[1], Bs[1][1], adjN, adjL, adjM); 
    p[2] = Strassen(s[2], Bs[0][0], adjN, adjL, adjM); 
    p[3] = Strassen(As[1][1], s[3], adjN, adjL, adjM); 
    p[4] = Strassen(s[4], s[5], adjN, adjL, adjM); 
    p[5] = Strassen(s[6], s[7], adjN, adjL, adjM); 
    p[6] = Strassen(s[8], s[9], adjN, adjL, adjM); 
  
    for (int i = 0; i < adjN; i++) { 
        for (int j = 0; j < adjM; j++) { 
            c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j]; 
            if (j + adjM < m) 
                c[i][j + adjM] = p[0][i][j] + p[1][i][j]; 
            if (i + adjN < n) 
                c[i + adjN][j] = p[2][i][j] + p[3][i][j]; 
            if (i + adjN < n && j + adjM < m) 
                c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j]; 
        } 
    } 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjN; i++) { 
                delete[] As[x][y][i]; 
            } 
            delete[] As[x][y]; 
        } 
        delete[] As[x]; 
    } 
    delete[] As; 
  
    for (int x = 0; x < 2; x++) { 
        for (int y = 0; y < 2; y++) { 
            for (int i = 0; i < adjL; i++) { 
                delete[] Bs[x][y][i]; 
            } 
            delete[] Bs[x][y]; 
        } 
        delete[] Bs[x]; 
    } 
    delete[] Bs; 
  
    for (int i = 0; i < 10; i++) { 
        switch (i) { 
        case 0: 
        case 3: 
        case 5: 
        case 7: 
        case 9: 
            for (int j = 0; j < adjL; j++) { 
                delete[] s[i][j]; 
            } 
            break; 
        case 1: 
        case 2: 
        case 4: 
        case 6: 
        case 8: 
            for (int j = 0; j < adjN; j++) { 
                delete[] s[i][j]; 
            } 
            break; 
        } 
        delete[] s[i]; 
    } 
    delete[] s; 
  
    for (int i = 0; i < 7; i++) { 
        for (int j = 0; j < (n >> 1); j++) { 
            delete[] p[i][j]; 
        } 
        delete[] p[i]; 
    } 
    delete[] p; 
  
    return c; 
} 

namespace utility
{
    int randomNumber(int lower, int upper)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(lower, upper);

        return dist(rng);
    }

    int randPartition(std::vector<int> &v, int p, int q)
    {
        int pivotIndex = p;
        int startPivotPos = randomNumber(0, v.size()-1);
        int pivot = v[startPivotPos];
        int t;

        //swap the pivot and the first pos
        v[startPivotPos] = v[p];
        v[p] = pivot;

        for (auto j = p+1; j<q-1; ++j)
        {
            if ( v[j] <= pivot ) 
            {
                ++pivotIndex;
                t = v[j];
                v[j] = v[pivotIndex];
                v[pivotIndex] = t;
            }
        }

        v[p] = v[pivotIndex];
        v[pivotIndex] = pivot;

        return pivotIndex;
    }
}

namespace sorting 
{
    int insertionSort(std::vector<int> &v)
    {
        int i, j, key, n = v.size();

        for ( j = 1; j<n; j++)
        {
            key = v[j];
            i = j-1;

            while ( i > 0 && v[i] > key ) 
            {   
                v[i+1] = v[i];
                i-=1;
            }

            v[i+1] = key;
        }

        return 0;
    }
    
    std::vector<int> _merge(std::vector<int> &v1, std::vector<int> &v2)
    {
        int i = 0, j = 0, k = 0;
        std::vector<int> v;

        while ( i < v1.size() && j < v2.size() )
        {
            if ( v1[i] <= v2[j] )
            {
                v.push_back(v1[i]);
                i++;
            }else 
            {
                v.push_back(v2[j]); 
                j++;
            }
        }

        while ( i < v1.size() )
        {
            v.push_back(v1[i]);
            i++;
        }

        while( j < v2.size() )
        {
            v.push_back(v2[j]); 
            j++;
        }

        return v;
    }

    int mergeSort(std::vector<int> &v)
    {
        std::vector<int> v1, v2;
        int n = v.size();

        if ( n == 1 ) return 0;
        
        for ( int i=0; i<v.size()/2; i++ )
            v1.push_back(v[i]);

        for ( int i=v.size()/2; i<v.size(); i++ )
            v2.push_back(v[i]);

        mergeSort(v1);
        mergeSort(v2);
        v = _merge(v1, v2);
    }

    int bubble_sort(std::vector<int> &v)
    {
        int i, j, a;
        
        for (i=0; i<v.size(); i++)
            for (j=0; j<v.size(); j++)
                if (v[i] > v[j])
                {
                    a = v[j];
                    v[j] = v[i];
                    v[i] = a;
                }

        return 0;
    }

    //compute k as the max number in the vector
    int counting_sort(std::vector<int> &a)
    {
        std::vector<int> b (a.size(), 0);
        int max = *std::max_element(a.begin(), a.end());

        std::vector<int> c (max+1, 0); 
        
        for (auto i : a)
            c[i]+=1;

        for (auto i = 1; i<=max; ++i)
            c[i] += c[i-1];

        for (int i = b.size()-1; i>=0; --i)
        {
            b[c[a[i]]-1] = a[i];
            --c[a[i]];
        }

        a = std::move(b);
        return 0;
    }

    //for the radix sort 
    int _counting_sort(std::vector<int> &a, int digitIndex)
    {
        std::vector<int> b (a.size(), 0);
        //always 10 bc we consider one digit at the time
        std::vector<int> c (10, 0); 
        
        for (auto i : a)
            c[(i/digitIndex) % 10]+=1;

        for (auto i = 1; i<10; ++i)
            c[i] += c[i-1];

        for (int i = b.size()-1; i>=0; --i)
        {
            b[c[(a[i]/digitIndex) % 10]-1] = a[i];
            --c[(a[i]/digitIndex) % 10];
        }

        a = std::move(b);
        return 0;
    }

    int _numDigits(int number)
    {
        int digits = 0;
        if (number < 0) digits = 1; 
        while (number) {
            number /= 10;
            digits++;
        }
        return digits;
    }

    int radix_sort(std::vector<int> &v)
    {
       int max = *std::max_element(v.begin(), v.end());
       int digitNum = _numDigits(max);
       int digitIndex = 1;

       for (auto i = 1; i <= digitNum; ++i)
       {
            _counting_sort(v, digitIndex);        
            digitIndex *= 10;
       }

       return 0;
    }
}

namespace orderStatistics
{
    int minimum(std::vector<int> &v)
    {
        int min = v[0];

        for (auto el : v)
            if (el < min) 
                min = el;

        return min;
    }

    int maximum(std::vector<int> &v)
    {
        int max = v[0];

        for (auto el : v)
            if (el > max) 
                max = el;

        return max;
    }

    int minmax(std::vector<int> &v, int& minOut, int& maxOut)
    {
        int min, max, i;

        if (v.size() % 2 != 0)
        {
            min = v[0];
            max = v[0];
            i = 1;
        }
        else if ( v[0] > v[1] )
        {
            min = v[1];
            max = v[0];
            i = 2;
        }else
        {
            min = v[0];
            max = v[1];
            i = 2;
        }
       
        while ( i < v.size() )
        {
            if ( v[i] < v[i+1] )
            {
                if ( v[i] < min ) min = v[i];
                if ( v[i+1] > max) max = v[i+1];
            }
            else
            {
                if ( v[i+1] < min ) min = v[i+1];
                if ( v[i] > max) max = v[i];
            }
            
            i+=2;
        }
       
        minOut = min;
        maxOut = max; 
        return 0;
    }

    int randSelect(std::vector<int> v, int p, int q, int i)
    {
        if ( p == q ) return v[p];

        int r = utility::randPartition(v, p, q);
        int k = r - p + 1;
        
        if ( k == i ) return v[r];
        
        if ( i < k ) 
            return randSelect(v, p, r-1, i);

        return randSelect(v, r+1, q, i-k);
    }
}

