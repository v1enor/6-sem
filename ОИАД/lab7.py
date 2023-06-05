import mglearn
import sklearn
import matplotlib.pyplot as plt
import numpy as np
from sklearn.naive_bayes import GaussianNB
from sklearn.naive_bayes import BernoulliNB
from sklearn.naive_bayes import MultinomialNB

# Классификатор BernoulliNB
X = np.array([[0, 1, 0, 1], [1, 0, 1, 1], [0, 0, 0, 1], [1, 0, 1, 0]])
y = np.array([0, 1, 0, 1])

counts = {}
for label in np.unique(y):
    counts[label] = X[y == label].sum(axis=0)
print("Частоты признаков:\n{}".format(counts))

clf = BernoulliNB()
clf.fit(X, y)
print(X[2:3])
print(clf.predict(X[2:3]))
# Классификатор MultinomialNB (принимает в расчет среднее значение кажд призн для кажд класса)

rng = np.random.RandomState(1)
X = rng.randint(5, size=(6, 100))
y = np.array([1, 2, 3, 4, 5, 6])

clf = MultinomialNB()
clf.fit(X, y)

print('Классификатор MultinomialNB')
print(X[2:3])
print(clf.predict(X[2:3]))

# Классификатор GaussianNB (записывает среднее значение и станд отклонение)
X = np.array([[-1, -1], [-2, -1], [-3, -2], [1, 1], [2, 1], [3, 2]])
Y = np.array([1, 1, 1, 2, 2, 2])
clf = GaussianNB()
clf.fit(X, Y)

print('Классификатор GaussianNB')
print([[-0.8, -1]])
print(clf.predict([[-0.8, -1]]))

clf_pf = GaussianNB()
clf_pf.partial_fit(X, Y, np.unique(Y))

print('Классификатор GaussianNB')
print([[-0.8, -1]])
print(clf_pf.predict([[-0.8, -1]]))