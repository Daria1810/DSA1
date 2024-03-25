#include <iostream>
#include <stack>
#include <fstream>

///am folosit biblioteca predefinita

int main()
{
    int n;
    int a[20][20];
    bool attended=false;

///citirea din fisier

    ifstream fin("matrix.txt");

    fin>>n;

    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
        {
            fin>>a[i][j];
        }

///creerea stack-ului

    stack<int> participants;

    for (int i = 1; i <= n; i++)
    {
        participants.push(i);
    }

///O(kN) aici NU e O(n^2), nici 2O(n^2)

    while (!participants.empty())
    {
        ///salveaza valoarea curenta ca ultima valoare din stack, si dupa o scoate din stack

        int currentParticipant = participants.top();

        participants.pop();

        ///variabile pentru testarea celor doua conditii care determina daca participantul verificat e homer

        bool everyoneTalkedToThem = true;
        bool hasTalkedToNobody = true;

        ///verificarea propriu-zisa

        for (int i = 0; i < n; i++)
        {
            if (i != currentParticipant && a[i][currentParticipant] == 0)
            {
                everyoneTalkedToThem = false;
                break;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (i != currentParticipant && a[currentParticipant][i] == 1)
            {
                hasTalkedToNobody = false;
                break;
            }
        }

        ///afisarea participantului care este homer

        if (everyoneTalkedToThem&&hasTalkedToNobody)
        {
            cout << "Homer is the participant number " << currentParticipant <<"."<< endl;
            attended=true;
            break;
        }
    }


    ///cazul in care homer nu participa

    if(attended==false)
        cout<<"Homer is not a participant!";

    return 0;
}

