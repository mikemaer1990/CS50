SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name == "Johnny Depp"
AND stars.movie_id IN
(SELECT movie_id FROM stars
WHERE person_id IN (SELECT id
FROM people WHERE name == "Helena Bonham Carter"))
ORDER BY title ASC;