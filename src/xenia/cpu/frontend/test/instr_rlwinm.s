test_rlwinm_extrwi:
  # extrwi ra,rs,n,b (n > 0) == rlwinm ra,rs,b+n,32-n,31
  #_ REGISTER_IN r5 0x30
  # rlwinm r7, r5, 29, 28, 31
  extrwi r7, r5, 4, 25
  blr
  #_ REGISTER_OUT r5 0x30
  #_ REGISTER_OUT r7 0x06

test_rlwinm_extrwi_constant:
  # extrwi ra,rs,n,b (n > 0) == rlwinm ra,rs,b+n,32-n,31
  li r5, 0x30
  # rlwinm r7, r5, 29, 28, 31
  extrwi r7, r5, 4, 25
  blr
  #_ REGISTER_OUT r5 0x30
  #_ REGISTER_OUT r7 0x06

test_rlwinm_1:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 24, 8, 15
  blr
  #_ REGISTER_OUT r3 0x00120000
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_1_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 24, 8, 15
  blr
  #_ REGISTER_OUT r3 0x00120000
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_2:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 4, 0, 27
  blr
  #_ REGISTER_OUT r3 0x23456780
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_2_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 4, 0, 27
  blr
  #_ REGISTER_OUT r3 0x23456780
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_3:
  #_ REGISTER_IN r4 0x90003000
  rlwinm r3, r4, 2, 0, 0x1D
  blr
  #_ REGISTER_OUT r3 0x4000C000
  #_ REGISTER_OUT r4 0x90003000

test_rlwinm_3_constant:
  lis r4, 0x9000
  ori r4, r4, 0x3000
  clrldi r4, r4, 32
  rlwinm r3, r4, 2, 0, 0x1D
  blr
  #_ REGISTER_OUT r3 0x4000C000
  #_ REGISTER_OUT r4 0x90003000

test_rlwinm_4:
  #_ REGISTER_IN r4 0xB0043000
  rlwinm. r3, r4, 2, 0, 0x1D
  blr
  #_ REGISTER_OUT r3 0xC010C000
  #_ REGISTER_OUT r4 0xB0043000
  # CRF = 0x8

test_rlwinm_4_constant:
  lis r4, 0xB004
  ori r4, r4, 0x3000
  clrldi r4, r4, 32
  rlwinm. r3, r4, 2, 0, 0x1D
  blr
  #_ REGISTER_OUT r3 0xC010C000
  #_ REGISTER_OUT r4 0xB0043000
  # CRF = 0x8

test_rlwinm_5:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 0, 5, 0x1D
  blr
  #_ REGISTER_OUT r3 0x02345678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_5_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 0, 5, 0x1D
  blr
  #_ REGISTER_OUT r3 0x02345678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_6:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 0, 0, 31
  blr
  #_ REGISTER_OUT r3 0x12345678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_6_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 0, 0, 31
  blr
  #_ REGISTER_OUT r3 0x12345678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_7:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 0, 0, 16
  blr
  #_ REGISTER_OUT r3 0x12340000
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_7_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 0, 0, 16
  blr
  #_ REGISTER_OUT r3 0x12340000
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_8:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 0, 16, 31
  blr
  #_ REGISTER_OUT r3 0x00005678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_8_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 0, 16, 31
  blr
  #_ REGISTER_OUT r3 0x00005678
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_9:
  #_ REGISTER_IN r4 0x12345678
  rlwinm r3, r4, 16, 16, 31
  blr
  #_ REGISTER_OUT r3 0x00001234
  #_ REGISTER_OUT r4 0x12345678

test_rlwinm_9_constant:
  lis r4, 0x1234
  ori r4, r4, 0x5678
  rlwinm r3, r4, 16, 16, 31
  blr
  #_ REGISTER_OUT r3 0x00001234
  #_ REGISTER_OUT r4 0x12345678
