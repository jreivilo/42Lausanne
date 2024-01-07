import { PartialType } from '@nestjs/swagger';
import { CreateUserDto } from '../../auth/dto/create-user.dto';

export class UpdateUserDto extends PartialType(CreateUserDto) {
    username: string;
    avatar: string;
    update_at: Date = new Date();
}
