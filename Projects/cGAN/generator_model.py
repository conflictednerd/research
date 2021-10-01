'''
NOTICE: Because of the skip connections we are concatenating encoders outputs with decoders output. Thus, the size of the input x
    to the generator MUST BE A POWER OF 2 so that after deconvolution layers, its dimension matches with that of encoder
'''
import torch
import torch.nn as nn
from torch.nn.modules import padding

class EncoderBlock(nn.Module):
    def __init__(self, in_channels: int, out_channels: int):
        super().__init__()
        self.model = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=4, stride=2, padding=1, bias=False, padding_mode='reflect'),
            nn.InstanceNorm2d(out_channels),
            nn.LeakyReLU(0.2)
        )

    def forward(self, x):
        return self.model(x)

class DecoderBlock(nn.Module):
    def __init__(self, in_channels: int, out_channels: int, has_dropout=False):
        super().__init__()
        self.model = nn.Sequential(
            nn.ConvTranspose2d(in_channels, out_channels, kernel_size=4, stride=2, padding = 1, bias=False),
            nn.InstanceNorm2d(out_channels),
            nn.ReLU()
        )
        self.has_dropout = has_dropout
        self.dropout = nn.Dropout2d(p = 0.5)

    def forward(self, x):
        x = self.model(x)
        return self.dropout(x) if self.has_dropout else x


class Generator(nn.Module):
    def __init__(self, in_channels: int = 3, out_channels: int = 3):
        super().__init__()
        self.enc0 = nn.Sequential(
            nn.Conv2d(in_channels, 64, kernel_size=4, stride=2, padding=1, padding_mode='reflect'),
            nn.LeakyReLU(0.2)
        )
        self.enc1 = EncoderBlock(64, 128)
        self.enc2 = EncoderBlock(128, 256)
        self.enc3 = EncoderBlock(256, 512)
        self.enc4 = EncoderBlock(512, 512)
        self.enc5 = EncoderBlock(512, 512)
        self.enc6 = EncoderBlock(512, 512)
        self.enc7 = nn.Sequential(
            nn.Conv2d(512, 512, kernel_size=4, stride=2, padding=1, padding_mode='reflect'),
            nn.ReLU()
        )

        self.dec0 = DecoderBlock(512, 512, has_dropout=True)
        self.dec1 = DecoderBlock(1024, 512, has_dropout=True)
        self.dec2 = DecoderBlock(1024, 512, has_dropout=True)
        self.dec3 = DecoderBlock(1024, 512)
        self.dec4 = DecoderBlock(1024, 256)
        self.dec5 = DecoderBlock(512, 128)
        self.dec6 = DecoderBlock(256, 64)
        self.dec7 = nn.Sequential(
            nn.ConvTranspose2d(128, out_channels, kernel_size=4, stride=2, padding = 1),
            nn.Tanh()
        )


    def forward(self, x):
        e0 = self.enc0(x) # C:64, dim/2
        e1 = self.enc1(e0) # C:128, dim/4
        e2 = self.enc2(e1) # C:256, dim/8
        e3 = self.enc3(e2) # C:512, dim/16
        e4 = self.enc4(e3) # C:512, dim/32
        e5 = self.enc5(e4) # C:512, dim/64
        e6 = self.enc6(e5) # C:512, dim/128
        e7 = self.enc7(e6) # C:512, dim/256

        d0 = self.dec0(e7) # C:512, dim/128
        d1 = self.dec1(torch.cat((d0, e6), dim=1)) # C:512, dim/64
        d2 = self.dec2(torch.cat((d1, e5), dim=1)) # C:512, dim/32
        d3 = self.dec3(torch.cat((d2, e4), dim=1)) # C:512, dim/16
        d4 = self.dec4(torch.cat((d3, e3), dim=1)) # C:256, dim/8
        d5 = self.dec5(torch.cat((d4, e2), dim=1)) # C:128, dim/4
        d6 = self.dec6(torch.cat((d5, e1), dim=1)) # C:64, dim/2
        d7 = self.dec7(torch.cat((d6, e0), dim=1)) # C:3, dim

        return d7

def test():
    x = torch.randn(1, 3, 512, 512)
    G = Generator(3, 3)
    y = G(x)
    print(y.shape)

if __name__ == '__main__':
    test()