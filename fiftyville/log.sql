-- Keep a log of any SQL queries you execute as you solve the mystery.
-- To begin running queries on the database
sqlite3 fiftyville.db
-- To now what table of information are in fiftyville.db
.tables
-- To now the information on the columns in crime_scene_reports table
.schema crime_scene_reports
-- find crime scene description
SELECT description FROM crime_scene_reports WHERE year = 2023 And month = 7 AND street = 'Humphrey Street';
-- find the name and transcripts of 3 eye witness
SELECT name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;
-- three witness are Ruth, Eugene and Raymond,ruth says theft uses a bakery parking within 10 minutes so we check the license_plate number, And EUgene gives info that he uses ATM on that day morning on the specific atm adress AND lastly Rymond gives information that the thief calls to someone to order plane ticket on the next day ealrliest flight out of fiftyville.
SELECT name FROM people
    WHERE people.license_plate IN (
       SELECT license_plate FROM bakery_security_logs
           WHERE year = 2023
    AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)
    AND people.id IN (
        SELECT person_id FROM bank_accounts WHERE account_number IN (
            SELECT account_number FROM atm_transactions WHERE year = 2023
    AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    ))
    AND people.phone_number IN(
        SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28)
    AND people.passport_number IN(
        SELECT passport_number FROM passengers WHERE flight_id IN(
            SELECT id FROM flights WHERE year = 2023 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
            )
            );

-- find the city that he arived
SELECT city FROM airports
-- from the first flight of that day from fiftyville
    WHERE id IN(
        SELECT destination_airport_id FROM flights
            WHERE year = 2023 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);
-- find acomplice name
SELECT name FROM people
    -- find his phone_number as he is reciever from call in duration of lessthan one minute call
    WHERE phone_number IN(
        SELECT receiver FROM phone_calls
        WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
        --by specific caller information name from we find earlier now we get acompliance
        AND caller IN (SELECT phone_number FROM people WHERE name = 'Bruce'));


