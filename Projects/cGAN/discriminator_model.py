'''
In the paper, they used batch norm, not isntance norm
I added a padding of 1 so that it downsamples by a factor of exactly 2
'''
import torch
import torch.nn as nn

class Block(nn.Module):
    def __init__(self, in_channels: int, out_channels: int):
        super().__init__()
        self.model = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=4, stride=2, padding=1, bias=False, padding_mode='reflect'),
            nn.InstanceNorm2d(out_channels),
            nn.LeakyReLU(0.2)
        )

    def forward(self, x):
        return self.model(x)


class Discriminator(nn.Module):
    def __init__(self, in_channels: int):
        super().__init__()
        self.b0 = nn.Sequential(
            nn.Conv2d(2*in_channels, 64, kernel_size=4, stride=2, padding=1, padding_mode='reflect'),
            nn.LeakyReLU(0.2)
        ) # input has 2 times image channels because it is a concatenation of the original image and the generated/transformed image
        self.b1 = Block(64, 128)
        self.b2 = Block(128, 256)
        self.b3 = Block(256, 512)
        self.b4 = nn.Sequential(
            nn.Conv2d(512, 1, kernel_size=4, stride=1, padding=1, padding_mode='reflect'),
            nn.Sigmoid()
        )

    def forward(self, x, y):
        x = torch.cat((x, y), dim=1)
        x = self.b0(x)
        x = self.b1(x)
        x = self.b2(x)
        x = self.b3(x)
        x = self.b4(x)
        return x


def test():
    d = Discriminator(3)
    s = 70
    x = torch.randn(1, 3, s, s)
    y = torch.randn(1, 3, s, s)
    z = d(x, y)

if __name__ == '__main__':
    test()