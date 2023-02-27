import matplotlib.pyplot as plt

def prrint_freg(plain_freq,cipher_freq):
    fig, ax = plt.subplots(2, 1)

    ax[0].bar(range(len(plain_freq)), plain_freq.values(), align='center')
    ax[0].set_xticks(range(len(plain_freq)))
    ax[0].set_xticklabels(list(plain_freq.keys()))
    ax[0].set_xlabel('Symbol')
    ax[0].set_ylabel('Frequency')
    ax[0].set_title('Frequencies of symbols in plaintext')

    for i, v in enumerate(plain_freq.values()):
        ax[0].text(i, v, str(v), ha='center', va='bottom')

    ax[1].bar(range(len(cipher_freq)), cipher_freq.values(), align='center')
    ax[1].set_xticks(range(len(cipher_freq)))
    ax[1].set_xticklabels(list(cipher_freq.keys()))
    ax[1].set_xlabel('Symbol')
    ax[1].set_ylabel('Frequency')
    ax[1].set_title('Frequencies of symbols in ciphertext')

    for i, v in enumerate(cipher_freq.values()):
        ax[1].text(i, v, str(v), ha='center', va='bottom')

    plt.tight_layout()
    plt.show()


def count_frequencies(text, alphabet):
    # функция для подсчета частот появления символов в тексте
    frequencies = {char: 0 for char in alphabet}
    for char in text:
        if char in frequencies:
            frequencies[char] += 1
    return frequencies