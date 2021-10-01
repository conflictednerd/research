import torch
from torch.utils.data import DataLoader
import torch.optim as optim
import torch.nn as nn
from tqdm import tqdm
from torchvision.utils import save_image

import config
import utils
from dataset import CustomDataset
from discriminator_model import Discriminator
from generator_model import Generator

def save_samples(loader: DataLoader, generator: Generator, epoch: int):
    with torch.no_grad():
        x, y = iter(loader).next()
        z = generator(x)
        images = torch.cat((x, y, z), dim = 3)
        # scale values from [-1, 1] to [0, 1]
        images += 1
        images /= 2
        for idx, image in enumerate(images):
            print('Writing images...')
            save_image(image, f'samples/e{epoch}i{idx}.jpg')
            


def main():
    train_set = CustomDataset(root=config.TRAIN_PATH)
    train_loader = DataLoader(train_set, batch_size=config.BATCH_SIZE, shuffle=True, num_workers=config.NUM_WORKERS)
    test_set = CustomDataset(root=config.TEST_PATH)
    test_loader = DataLoader(test_set, batch_size=config.BATCH_SIZE, shuffle=False, num_workers=config.NUM_WORKERS)

    disc = Discriminator(in_channels=3).to(config.DEVICE)
    gen = Generator(in_channels=3, out_channels=3).to(config.DEVICE)

    disc_opt = optim.Adam(disc.parameters(), lr=config.LR, betas=(config.BETA_1, config.BETA_2))
    gen_opt = optim.Adam(gen.parameters(), lr=config.LR, betas=(config.BETA_1, config.BETA_2))

    BCE = nn.BCELoss()
    L1 = nn.L1Loss()

    for epoch in range(config.EPOCHS):

        disc_running_loss, gen_running_loss = 0, 0
        for i, (x, y) in enumerate(tqdm(train_loader)):
            x = x.to(config.DEVICE)
            y = y.to(config.DEVICE)
            disc_opt.zero_grad()
            gen_opt.zero_grad()

            y_fake = gen(x)
            # Training the discriminator
            fake_prediction = disc(x, y_fake.detach())
            real_prediction = disc(x, y)
            disc_loss = BCE(fake_prediction, torch.zeros_like(fake_prediction)) + BCE(real_prediction, torch.ones_like(real_prediction))
            disc_loss /= 2 # Specified in the paper to slow down discriminators training

            disc_loss.backward()
            disc_opt.step()
            disc_running_loss += disc_loss

            # Training the generator
            fake_prediction = disc(x, y_fake)
            gen_loss = BCE(fake_prediction, torch.ones_like(fake_prediction)) + config.LAMBDA * L1(y_fake, y)

            gen_loss.backward()
            gen_opt.step()
            gen_running_loss += gen_loss
            if i % 20 == 0:
                save_samples(test_loader, gen, epoch)

        print(f'[EPOCH {epoch} is done] : generator loss is {gen_running_loss}, discriminator loss is {disc_running_loss}')
        save_samples(test_loader, gen, epoch)
        if epoch % 2 == 0:
            print('Saving...')
            utils.save(config.DISC_CHECKPOINT, disc, disc_opt, epoch)
            utils.save(config.GEN_CHECKPOINT, gen, gen_opt, epoch)
            



if __name__ == '__main__':
    main()