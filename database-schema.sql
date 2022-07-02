CREATE TABLE authors
(
  author_id INT NOT NULL,
  author_name VARCHAR,
  PRIMARY KEY (author_id)
);

CREATE TABLE venue
(
  venue_name VARCHAR NOT NULL,
  venue_id INT NOT NULL,
  PRIMARY KEY (venue_id)
);

CREATE TABLE Research_paper
(
  paper_title VARCHAR NOT NULL,
  date_of_publication INT NOT NULL,
  abstract VARCHAR ,
  paper_id INT NOT NULL,
  author_id INT NOT NULL,
  venue_id INT NOT NULL,
  PRIMARY KEY (paper_id),
  FOREIGN KEY (author_id) REFERENCES authors(author_id),
  FOREIGN KEY (venue_id) REFERENCES venue(venue_id)
);

CREATE TABLE co_authors
(
  paper_id INT NOT NULL,
  author_id INT NOT NULL,
  PRIMARY KEY (paper_id, author_id),
  FOREIGN KEY (paper_id) REFERENCES Research_paper(paper_id),
  FOREIGN KEY (author_id) REFERENCES authors(author_id)
);

CREATE TABLE reference
(
  paper_id_1 INT NOT NULL,
  referencepaper_id_2 INT NOT NULL,
  PRIMARY KEY (paper_id_1, referencepaper_id_2),
  FOREIGN KEY (paper_id_1) REFERENCES Research_paper(paper_id),
  FOREIGN KEY (referencepaper_id_2) REFERENCES Research_paper(paper_id)
);
