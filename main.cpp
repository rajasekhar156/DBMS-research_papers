#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
int authorid = 1;
int venueid = 1;

vector<struct researchpaper> Paper;

map<string, int> Author_map;
map<string, int> Venue_map;

struct researchpaper
{
    int paper_id;
    int year;
    int mainauthor_id;
    int paper_venue_id;
    string paper_title;
    string abstract;
};

struct coauthor
{
    int paper_id;
    vector<int> coauthor_id;
};

struct reference
{
    int paper_id;
    vector<int> reference_ids;
};

int main()
{
    int i;
    ifstream fin;
    fin.open("source.txt");
    string tempstr;

    ofstream fout_paper;
    fout_paper.open("paper_table.csv");
    struct researchpaper *Paper_t = (struct researchpaper *)malloc(sizeof(struct researchpaper));

    ofstream fout_author;
    fout_author.open("author_table.csv");
    fout_author << "-1"
                << "\u0004RAJASEKHARITREDDY" << endl;
    //struct author *Author_t = (struct author*)malloc(sizeof(struct author));

    ofstream fout_venue;
    fout_venue.open("venue_table.csv");
    fout_venue << "-1"
               << "\u0004RAJASEKHARITREDDY" << endl;
    //struct venue *Venue_t = (struct venue*)malloc(sizeof(struct venue));

    ofstream fout_coauthor;
    fout_coauthor.open("coauthor_table.csv");
    struct coauthor *COauthor_t = (struct coauthor *)malloc(sizeof(struct coauthor));

    ofstream fout_referpaper;
    fout_referpaper.open("references_table.csv");
    struct reference *References_t = (struct reference *)malloc(sizeof(struct reference));

    while (getline(fin, tempstr))
    {
        if (tempstr[0] == '\0')
        {
            fout_paper << Paper_t->paper_id << "\u0004" << Paper_t->year << "\u0004" << Paper_t->mainauthor_id << "\u0004" << Paper_t->paper_title << "\u0004" << Paper_t->paper_venue_id << "\u0004" << Paper_t->abstract << endl;
            set<int> coauthorid_set(COauthor_t->coauthor_id.begin(), COauthor_t->coauthor_id.end());
            for (auto itr = coauthorid_set.begin(); itr != coauthorid_set.end(); itr++)
            {
                fout_coauthor << Paper_t->paper_id << "\u0004" << *itr << endl;
            }
            COauthor_t->coauthor_id.clear();
            set<int> referpaper_set(References_t->reference_ids.begin(), References_t->reference_ids.end());
            for (auto itr = referpaper_set.begin(); itr != referpaper_set.end(); itr++)
            {
                if (*itr != Paper_t->paper_id)
                    fout_referpaper << Paper_t->paper_id << "\u0004" << *itr << endl;
            }
            References_t->reference_ids.clear();
        }
        else if (tempstr[0] == '#' && tempstr[1] == '*')
        {
            string temp = tempstr.substr(2);
            Paper_t->paper_title = temp;
        }
        else if (tempstr[0] == '#' && tempstr[1] == '!')
        {
            string temp = tempstr.substr(2);
            Paper_t->abstract = temp;
        }
        else if (tempstr[0] == '#' && tempstr[1] == 't')
        {
            string temp = tempstr.substr(2);
            Paper_t->year = stoi(temp);
        }
        else if (tempstr[0] == '#' && tempstr[1] == 'i')
        {
            string temp = tempstr.substr(6);
            Paper_t->paper_id = stoi(temp);
        }
        else if (tempstr[0] == '#' && tempstr[1] == '%')
        {
            string temp = tempstr.substr(2);
            References_t->reference_ids.push_back(stoi(temp));
        }
        else if (tempstr[0] == '#' && tempstr[1] == '@')
        {
            if (tempstr[2] != '\0')
            {
                int pos = 0;
                string temp;
                pos = tempstr.find(",");
                if (pos > 0)
                    temp = tempstr.substr(2, pos - 2);
                else
                    temp = tempstr.substr(2);

                if (!Author_map[temp])
                {
                    Author_map[temp] = authorid;
                    fout_author << authorid << "\u0004" << temp << endl;
                    Paper_t->mainauthor_id = authorid;
                    authorid++;
                }
                else
                {
                    Paper_t->mainauthor_id = Author_map[temp];
                }
                if (pos > 0)
                {
                    tempstr = tempstr.substr(pos + 1);
                    while (1)
                    {
                        pos = 0;
                        i = pos;
                        pos = tempstr.find(",");
                        if (pos > 0 || (pos == 0 && tempstr.length() > 1))
                        {

                            temp = tempstr.substr(i, pos);

                            if (!Author_map[temp])
                            {
                                Author_map[temp] = authorid;
                                fout_author << authorid << "\u0004" << temp << endl;
                                COauthor_t->coauthor_id.push_back(authorid);
                                authorid++;
                            }
                            else
                            {
                                COauthor_t->coauthor_id.push_back(Author_map[temp]);
                            }
                            tempstr = tempstr.substr(pos + 1);
                        }
                        else
                        {
                            temp = tempstr.substr(i);
                            if (!Author_map[temp])
                            {
                                Author_map[temp] = authorid;
                                fout_author << authorid << "\u0004" << temp << endl;
                                COauthor_t->coauthor_id.push_back(authorid);
                                authorid++;
                            }
                            else
                            {
                                COauthor_t->coauthor_id.push_back(Author_map[temp]);
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                Paper_t->mainauthor_id = -1;
            }
        }
        else if (tempstr[0] == '#' && tempstr[1] == 'c')
        {
            string temp;
            if (tempstr[2] != '\0')
            {
                int i = 0;
                int temp_t = 0;
                temp = tempstr.substr(2);
                if (!Venue_map[temp])
                {
                    Venue_map[temp] = venueid;
                    fout_venue << venueid << "\u0004" << temp << endl;
                    Paper_t->paper_venue_id = venueid;
                    venueid++;
                }
                else
                {
                    Paper_t->paper_venue_id = Venue_map[temp];
                }
            }
            else
            {
                Paper_t->paper_venue_id = -1;
            }
        }
    }
    return 0;
}