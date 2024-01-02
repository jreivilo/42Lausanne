import { $Enums, Users } from '@prisma/client';
import { ApiProperty } from '@nestjs/swagger';

export class UserEntity implements Users {
  @ApiProperty()
  id: number;

  @ApiProperty()
  login: string;

  @ApiProperty()
  username: string;

  @ApiProperty()
  status: $Enums.Status;

  @ApiProperty()
  avatar: string;

  @ApiProperty()
  twofactor: boolean;

  @ApiProperty()
  hash2FA: string;
  
  @ApiProperty()
  create_at: Date;
  
  @ApiProperty()
  update_at: Date;
  
  @ApiProperty()
  delete_at: Date;

  @ApiProperty()
  tournamentsId: number | null;
}
