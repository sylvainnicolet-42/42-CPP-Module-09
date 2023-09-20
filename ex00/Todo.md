# Todo

- [x] Store db_filename in a map container
- [x] Create a function getExchangeRateWithDate
  - [ ] Return float instead of string
- [ ] Check validity of date (Year-Month-Day)
- [ ] Check validity of value (float between 0 and 1000)
- [ ] Create function to display the result for each line

## Results
- 2011-01-03 => 3 = 0.9
- 2011-01-03 => 2 = 0.6 (Date not found, the lowest date is used)
- Error: not a positive number.
- Error: bad input => 2001-42-42
- Error: too large a number.
- Error: no date found.