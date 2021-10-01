import torch
from torch.nn import Module
from torch.optim import Optimizer

def save(name: str, model: Module, optimizer: Optimizer, epoch: int):
    torch.save({
        'epoch': epoch,
        'model_state_dict': model.state_dict(),
        'optimizer_state_dict': optimizer.state_dict(),
    }, name)

def load(name: str, model: Module, optimizer: Optimizer):
    checkpoint = torch.load(name)
    model.load_state_dict(checkpoint['model_state_dict'])
    optimizer.load_state_dict(checkpoint['optimizer_state_dict'])

    model.train()