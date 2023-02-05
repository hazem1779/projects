-- Keep a log of any SQL queries you execute as you solve the mystery.
--witnesses
Ruth | 161
Eugene | 162
Raymond | 163

SELECT id,license_plate,activity,minute FROM courthouse_security_logs
WHERE month = 7 AND day= 28 AND year = 2020
AND hour = 10 

260 | 5P2BI95 | exit | 16
261 | 94KL13X | exit | 18 *****
262 | 6P58WS2 | exit | 18
263 | 4328GD8 | exit | 19 *****
264 | G412CB7 | exit | 20
265 | L93JTIZ | exit | 21 *****
266 | 322W7JE | exit | 23 *****
267 | 0NTHK55 | exit | 23

SELECT id,account_number,amount FROM atm_transactions
WHERE month = 7 AND day= 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location="Fifer Street";
246 | 28500762 | 48
264 | 28296815 | 20
266 | 76054385 | 60
267 | 49610011 | 50
269 | 16153065 | 80
288 | 25506511 | 20
313 | 81061156 | 30
336 | 26013199 | 35



SELECT name,phone_number,passport_number,license_plate FROM people WHERE id IN
(
SELECT person_id FROM bank_accounts
WHERE account_number IN(
SELECT account_number FROM atm_transactions
WHERE month = 7 AND day= 28 AND year = 2020
AND transaction_type = "withdraw"
AND atm_location="Fifer Street"
)
);
name | phone_number | passport_number | license_plate
Bobby | (826) 555-1652 | 9878712108 | 30G67EN
Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ *****
Victoria | (338) 555-6650 | 9586786673 | 8X428L0
Madison | (286) 555-6063 | 1988161715 | 1106N58
Roy | (122) 555-4581 | 4408372428 | QX4YZN3
Danielle | (389) 555-5198 | 8496433585 | 4328GD8 ****
Russell | (770) 555-1861 | 3592750733 | 322W7JE ****
Ernest | (367) 555-5533 | 5773159633 | 94KL13X *****

-- closest group

--Danielle | (389) 555-5198 | 8496433585 | 4328GD8

--(609) 555-5876 | (389) 555-5198  | 60
--36 | 8496433585 | 7B

--Russell | (770) 555-1861 | 3592750733 | 322W7JE 
--(770) 555-1861 | (725) 555-3243 | 49
--18 | 3592750733 | 4C

Ernest | (367) 555-5533 | 5773159633 | 94KL13X 
(367) 555-5533 | (375) 555-8161 | 45
(367) 555-5533 | (704) 555-5790 | 75
36 | 5773159633 | 4A

SELECT caller,receiver,duration FROM phone_calls WHERE 
month = 7 AND day= 28 AND year = 2020
AND caller LIKE "%(367)%" 


 SELECT * FROM passengers WHERE flight_id = 36 
 IN(
 SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city="Fiftyville")
 AND month = 7 AND day= 29 AND year = 2020);
 
 



SELECT id,destination_airport_id,hour,minute FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city="Fiftyville")
AND month = 7 AND day= 29 AND year = 2020;

id | destination_airport_id | hour | minute
18 | 6 | 16 | 0
23 | 11 | 12 | 15
36 | 4 | 8 | 20 **********
43 | 1 | 9 | 30
53 | 9 | 15 | 20


6121106406