'''
TODO: Add Augmentations -> NOTICE: x, y should be transformed exactly the same
'''
from torchvision.transforms import Compose, ToTensor
from torch.utils.data import Dataset, DataLoader, dataloader
import os
import cv2 as cv


class CustomDataset(Dataset):
    def __init__(self, root: str):
        super().__init__()
        self.root = root
        self.file_names = os.listdir(self.root)
        self.transform = Compose([
            ToTensor(),
        ])

    def __len__(self):
        return len(self.file_names)

    def __getitem__(self, index):
        path = self.root + '/' + self.file_names[index]
        img = cv.imread(path).astype('float32')
        img /= (255 / 2)  # values in [0, 2]
        img -= 1  # values in [-1, 1]

        x = img[:, :img.shape[1]//2, :]
        y = img[:, img.shape[1]//2:, :]
        if self.transform:
            x = self.transform(x)
            y = self.transform(y)
        return x, y


def test():
    test_set = CustomDataset(root='data/maps/val')
    test_loader = DataLoader(test_set, batch_size=8, shuffle=True, num_workers=2)
    x, y = iter(test_loader).next()
    print(x.shape, y.shape)


if __name__ == '__main__':
    test()
