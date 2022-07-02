1) first of all download the given file and extract the files.

2) now copy the source.txt file to this folder

3) Use the commands "g++ main.cpp" and press ENTER

4) now use the command "./a.out" and press ENTER

5) wait for about 15-20sec now we will get created 5 .csv files 

6) here we use one command that to remove all " and convert it into "" so that it does not interfere when loading into the tables
like this we have to do for both authors as well as Research_paper csv files;

    -> "sed 's/\"/\"\"/g' (oldfilename) > (newfilename);"

7) to initialize postgres type 

    -> "sudo -i -u postgres" 
    -> "psql"

8) now first to create the tables create a database named temp use

    -> "-i postgres database temp"
    -> "\c temp"

9)now you will be connected to temp database. to create tables use 

    ->"\i /*...sql file address....*/;"

10) now type the commands to get loaded from .csv files to database

    -> "copy authors(author_id ,author_name) from /*......new_author_table.csv address */ with csv delimiter E'\u0004' encoding 'utf-8';
    -> "copy venue(venue_id ,venue_name) from /*......venue_table.csv address */ with csv delimiter E'\u0004' encoding 'utf-8';
    -> "copy Research_paper(paper_id ,date_of_publication , author_id , paper_title , venue_id , abstract) from /*......new_paper_table.csv address */ with csv delimiter E'\u0004' encoding 'utf-8';
    -> "copy co_authors(paper_id ,author_id) from /*......c0author_table.csv address */ with csv delimiter E'\u0004' encoding 'utf-8';
    -> "copy reference(paper_id ,referencepaper_id_2) from /*......references_table.csv address */ with csv delimiter E'\u0004' encoding 'utf-8';


pg_dump <databaseName> > dump.sql
