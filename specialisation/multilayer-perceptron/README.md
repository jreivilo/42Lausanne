# multilayer_pereptron

#split + startardize etc...
python src/split.py --path data/data.csv          

python src/train.py --layer 32 64 32 16 --epochs 200 --loss binaryCrossentropy --batch_size 32 --learning_rate 0.001 --early_stopping 3

python src/train.py --layer 32 64 32 16 --epochs 200 --loss binaryCrossentropy --batch_size 32 --learning_rate 0.001

python src/predict.py

Bonus
- Accuracy training
- save losses
- standardize and normalize
- early stopping
- recap layers