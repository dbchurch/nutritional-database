curl -o nutrition.zip https://www.ars.usda.gov/ARSUserFiles/80400525/Data/BFPDB/BFPD_csv_07132018.zip
unzip nutrition.zip

grep -e "Carbohydrate" Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Carbohydrate, by difference/Carbohydrate/g' |cut -d~ -f1,5|sort>carbs
grep -e "Energy" Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g'|cut -d~ -f1,5|sort >energy
grep -e "Total lipid" Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |sed 's/Total lipid (fat)/Fat/g' |cut -d~ -f1,5|sort>fat
grep -e "Protein" Nutrients.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,5|sort>protein

cat Products.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1,2,5|sort>product
cat Serving_size.csv|sed 's/\",\"/~/g'|sed 's/^"//g' |cut -d~ -f1-5|sort>serving

join -t \~ energy carbs>ec
join -t \~ fat protein>fp
join -t \~ ec fp >nutrients
join -t \~ product nutrients >pn
join -t \~ pn serving >food_database.csv

