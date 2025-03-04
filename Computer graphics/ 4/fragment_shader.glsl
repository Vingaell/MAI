#version 330 core

in vec3 FragPos;       // Позиция фрагмента в мировых координатах
in vec3 Normal;        // Нормаль фрагмента
in vec2 TexCoord;      // Текстурные координаты

uniform vec3 viewPos;         // Позиция камеры
uniform vec3 dirLightDirection; // Направление направленного света
uniform vec3 pointLightPosition; // Позиция точечного света

uniform sampler2D ourTexture;  // Текстура
uniform sampler2D normalMap;   // Нормальная карта
uniform bool useNormalMap;     // Флаг использования нормальной карты

out vec4 FragColor;

// Функция для расчета направленного света с учетом угла
vec3 CalcDirLight(vec3 normal, vec3 lightDir) {
    // Вычисляем косинус угла между нормалью и направлением света
    float diff = max(dot(normal, -lightDir), 0.0);
    diff = diff * diff; // Применяем ослабление интенсивности на основе угла (например, квадратичное затухание)
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0); // Диффузное освещение

    // Спекулярное освещение
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0, 1.0, 1.0); // Спекулярное освещение

    return diffuse + specular;
}

// Функция для расчета точечного света с учетом расстояния
vec3 CalcPointLight(vec3 normal, vec3 lightPos) {
    vec3 lightDir = normalize(lightPos - FragPos);

    // Освещение по расстоянию (затухание)
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (distance * distance); // Простая модель затухания на основе расстояния
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    // Спекулярное освещение
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * vec3(1.0, 1.0, 1.0);

    // Применяем ослабление затухания для точки
    return attenuation * (diffuse + specular);
}

void main() {
    vec3 normal = normalize(Normal);

    // Если включено использование нормальной карты, читаем её
    if (useNormalMap) {
        vec3 tangentNormal = texture(normalMap, TexCoord).rgb;
        tangentNormal = normalize(tangentNormal * 2.0 - 1.0); // Нормализуем нормаль из диапазона [0, 1] в [-1, 1]
        normal = normalize(tangentNormal); // Переназначаем нормаль
    }

    // Освещение от направленного света с учетом угла
    vec3 dirLight = CalcDirLight(normal, dirLightDirection);

    // Освещение от точечного света с учетом расстояния
    vec3 pointLight = CalcPointLight(normal, pointLightPosition);

    // Итоговое освещение
    vec3 lighting = dirLight + pointLight;

    // Применяем текстуру
    vec3 textureColor = texture(ourTexture, TexCoord).rgb;

    // Итоговый цвет фрагмента
    FragColor = vec4(lighting * textureColor, 1.0);
}


