#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Policy
{
protected:
    bool isChecked;
public:
    virtual void check(const std::string & parola) = 0;
    bool getCheck() const
    {
        return isChecked;
    }
};

class LengthPolicy: public Policy
{
private:
    uint16_t minLength;
    uint16_t maxLength;
public:
    LengthPolicy(uint16_t minim)
    {
        minLength = minim;
        maxLength = 255;
    }
    LengthPolicy(uint16_t minim, uint16_t maxim)
    {
        minLength = minim;
        maxLength = maxim;
    }
    void check(const std::string & password)
    {
        if(password.size()<minLength || password.size()>maxLength)
        {
            isChecked = false;
        }
        else
        {
            isChecked = true;
        }
    }
};

class ClassPolicy : public Policy
{
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t minim)
    {
        minClassCount = minim;
    }
    void check(const std::string & password)
    { int cifre, mari,mici,caractere;
        cifre = 0;
        mici = 0;
        mari = 0;
        caractere = 0;
        int total = 0;
        for(int i=0;i<password.size();i++)
        {
            if (isdigit(password.at(i))) {
                cifre++;
            } else {
                if (password[i] >= 97 && password[i] <= 122) {
                    mici++;
                }
                else
                { if (password[i] >= 65 && password[i] <= 90) {
                        mari++;}
                    else
                        caractere++;
                }

            }
        }
        if(mici!=0)
            total++;
        if(mari!=0)
            total++;
        if(cifre!=0)
            total++;
        if(caractere!=0)
            total++;
        if(total <minClassCount)
            isChecked = false;
        else
            isChecked = true;
    }

};

class IncludePolicy : public Policy
{
private:
    char characterType;
public:
    IncludePolicy(char c)
    {
        characterType = c;
    }

    void check(const std::string & password)
    {   isChecked = false;
        if(characterType == 'A')
        {
            for(int i=0;i<password.size();i++)
            {
                if(password[i] >='A' && password[i]<='Z')
                    isChecked = true;
            }
        }
        else
        {
            if(characterType == '0')
            {
                for(int i=0;i<password.size();i++)
                {
                    if(password[i] >='0' && password[i]<='9')
                        isChecked = true;
                }
            }
            else
            {
                if(characterType == 'a')
                {
                    for(int i=0;i<password.size();i++)
                    {
                        if(password[i] >='a' && password[i]<='z')
                            isChecked = true;
                    }
                }
                else
                {  for(int i=0;i<password.size();i++)
                        if(password[i]<48 || password[i]>58 && password[i]<=64 || password[i]>=91 && password[i]<=96 || password[i]>=123)
                        {
                            isChecked = true;
                        }


                }
            }
        }
    }

};

class NotIncludePolicy : public Policy
{
private:
    char characterType;
public:
    NotIncludePolicy(char c)
    {
        characterType = c;
    }

    void check(const std::string & password)
    {   isChecked = true;
        if(characterType == 'A')
        {
            for(int i=0;i<password.size();i++)
            {
                if(password[i] >='A' && password[i]<='Z')
                    isChecked = false;
            }
        }
        else
        {
            if(characterType == '0')
            {
                for(int i=0;i<password.size();i++)
                {
                    if(password[i] >='0' && password[i]<='9')
                        isChecked = false;
                }
            }
            else
            {
                if(characterType == 'a')
                {
                    for(int i=0;i<password.size();i++)
                    {
                        if(password[i] >='a' && password[i]<='z')
                            isChecked = false;
                    }
                }
                else
                {   for(int i=0;i<password.size();i++)
                        if(password[i]<48 || password[i]>58 && password[i]<=64 || password[i]>=91 && password[i]<=96 || password[i]>=123)
                        {
                            isChecked = false;
                        }


                }
            }
        }
    }

};

class RepetitionPolicy: public Policy
{
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t max)
    {
        maxCount = max;
    }
    void check(const std::string & password)
    {
        int m = 0;
        isChecked = true;
        for(int i=0; i<password.size()-1; i++)
        {
            if(password[i] == password[i+1])
                m++;
            else
            {
                if(m+1 > maxCount)
                    isChecked = false;
                m = 0;
            }
        }
    }
};

class ConsecutivePolicy: public Policy
{
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t max)
    {
        maxCount = max;
    }
    void check(const std::string & password)
    {
        int m = 0;
        isChecked = true;
        for(int i=0; i<password.size()-1; i++)
        {
            if(password[i]+1 == password[i+1])
                m++;
            else
            {
                if(m+1 > maxCount)
                    isChecked = false;
                m = 0;
            }
        }
    }
};

string checkPassword(string  parola, vector <Policy*> u)
{
    for(int i=0;i<u.size();i++)
    {
        u[i]->check(parola);
    }
    for(int i=0;i<u.size();i++)
    {if(u[i]->getCheck()==false)
            return "NOK";
    }

    return "OK";

}

int main()
{
    int n;
    cin>>n;
    uint16_t maxx, minn;
    string cuvant;
    char c;
    vector <Policy*> v;
    string parola;
    int m=n;
    for(int i=0;i<m;i++)
    {
        cin>>cuvant;
        if(cuvant == "length")
        {
            cin>>minn;

            if(!scanf(" %d" ,&maxx))
                v.push_back(new LengthPolicy(minn));
            else
                v.push_back(new LengthPolicy(minn,maxx));
        }

        if(cuvant == "class")
        {
            cin>>minn;
            v.push_back(new ClassPolicy(minn));
        }

        if(cuvant == "include")
        {
            cin>>c;
            v.push_back(new IncludePolicy(c));

        }

        if(cuvant == "ninclude")
        {
            cin>>c;
            v.push_back(new NotIncludePolicy(c));
        }

        if(cuvant == "repetition")
        {
            cin>>maxx;
            v.push_back(new RepetitionPolicy(maxx));
        }

        if(cuvant == "consecutive")
        {
            cin>>maxx;
            v.push_back(new ConsecutivePolicy(maxx));

        }


    }

    while(cin>>parola)
    {
        cout<<checkPassword(parola, v)<<endl;
    }

    return 0;
}