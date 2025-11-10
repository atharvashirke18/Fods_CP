#!/usr/bin/env python3
"""
Generate simple WAV audio files for testing SFML audio playback.
"""
import os
import struct
import math

def create_wav_file(filename, duration_ms=2000, frequency=440, sample_rate=44100):
    """Create a simple sine wave WAV file."""
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    
    num_samples = int((duration_ms / 1000.0) * sample_rate)
    
    # WAV header
    num_channels = 1
    bytes_per_sample = 2
    byte_rate = sample_rate * num_channels * bytes_per_sample
    block_align = num_channels * bytes_per_sample
    
    with open(filename, 'wb') as f:
        # RIFF header
        f.write(b'RIFF')
        f.write(struct.pack('<I', 36 + num_samples * bytes_per_sample))
        f.write(b'WAVE')
        
        # fmt subchunk
        f.write(b'fmt ')
        f.write(struct.pack('<I', 16))  # Subchunk1Size
        f.write(struct.pack('<H', 1))   # AudioFormat (PCM)
        f.write(struct.pack('<H', num_channels))
        f.write(struct.pack('<I', sample_rate))
        f.write(struct.pack('<I', byte_rate))
        f.write(struct.pack('<H', block_align))
        f.write(struct.pack('<H', 16))  # BitsPerSample
        
        # data subchunk
        f.write(b'data')
        f.write(struct.pack('<I', num_samples * bytes_per_sample))
        
        # Generate sine wave
        for i in range(num_samples):
            t = i / sample_rate
            sample = int(32767 * 0.5 * math.sin(2 * math.pi * frequency * t))
            f.write(struct.pack('<h', sample))

# Create test audio files
test_songs = [
    ('test_song_1.wav', 3000, 440),   # A4, 3 seconds
    ('test_song_2.wav', 3000, 550),   # C#5, 3 seconds
    ('test_song_3.wav', 3000, 660),   # E5, 3 seconds
    ('test_song_4.wav', 3000, 880),   # A5, 3 seconds
]

for song_name, duration, frequency in test_songs:
    filepath = f'/home/lucifer/projects/Fods_CP/data/songs/{song_name}'
    create_wav_file(filepath, duration, frequency)
    print(f'Created {filepath}')

print('Test audio files created successfully!')
