SELECT title FROM movies
JOIN stars on stars.movie_id = movies.id
JOIN people on stars.person_id = people.id
JOIN ratings ON ratings.movie_id = movieS.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC lIMIT 5;
